// service_applicationOutputHandler.c
// 
// creator: John-William Lebel et Philippe Lemoine
// date: 2020-11-18

#include "service_applicationOutputHandler.h"
#include "main.h"
#include "../baseDeTemps/serviceBaseDeTemps.h"
#include "../communication/service_can.h"

#include "../math/service_bitOperation.h"

#include "../stepperMotor/service_stepperMotor.h"
#include "../lightHandling/machine/service_lightHandler.h"
#include "../triac/service_triac.h"

#include "../../interface/carteIO/interface_pcf8574A.h"
#include "../../interface/carteIO/interface_mcp3021.h"

#include "../../interface/lightColumn/interface_greenLight.h"
#include "../../interface/lightColumn/interface_yellowLight.h"
#include "../../interface/lightColumn/interface_redLight.h"

#include "../../interface/carteTriac/interface_stepperMotor.h"
#include "../../interface/carteTriac/interface_triac.h"

unsigned char valueOfOutputBoard0;
unsigned char previousValueOfOutputBoard0;

unsigned char valueOfOutputBoard1;
unsigned char previousValueOfOutputBoard1;

unsigned char valueOfLightColumn;
unsigned char previousValueOfLightColumn;

unsigned char stepMotorState;
unsigned char previousStepMotorState;

unsigned char triacState;
unsigned char previousTriacState;

// data struct
service_applicationOutputHandler_Data service_applicationOutputHandler_data;

service_stepperMotor_Stepper service_applicationOutputHandler_stepper = {0, 0, 50, 0, interface_stepperMotor_writeOutputByte};

service_lightHandler_Light service_applicationOutputHandler_greenLight = {SERVICE_LIGHTHANDLER_OFF, 0, 500, 500, interface_greenLight_writeOutputByte};
service_lightHandler_Light service_applicationOutputHandler_yellowLight = {SERVICE_LIGHTHANDLER_OFF, 0, 500, 500, interface_yellowLight_writeOutputByte};
service_lightHandler_Light service_applicationOutputHandler_redLight = {SERVICE_LIGHTHANDLER_OFF, 0, 500, 500, interface_redLight_writeOutputByte};

service_triac_Triac service_applicationOutputHandler_triac = {0.5, 0, interface_triac_writeTriacValue, interface_triac_isPassingByZero};

void updateDesiredStateOfBoard0();
void updateDesiredStateOfBoard1();
void setPhysicalOutputs();

// public function
void service_applicationOutputHandler_init() {
    valueOfOutputBoard0 = 0;
    previousValueOfOutputBoard0 = 0;
    
    valueOfOutputBoard1 = 0;
    previousValueOfOutputBoard1 = 0;
    
    // triac
    service_triac_init(&service_applicationOutputHandler_triac);
    
    // stepper
    service_stepperMotor_init(&service_applicationOutputHandler_stepper);
    
    // lights
    interface_greenLight_init();
    interface_yellowLight_init();
    interface_redLight_init();
    service_lightHandler_init();
    
    // can
    service_can_init();
    
    serviceBaseDeTemps_execute[SERVICEBASEDETEMPS_PHASE_UPDATE_APP_OUTPUTS]
        = service_applicationOutputHandler_update;
}

void service_applicationOutputHandler_update() {
    updateDesiredStateOfBoard0();
    updateDesiredStateOfBoard1();
    
    setPhysicalOutputs();
    // please refer to the connection table and schematic in the documentation for further info on physical connections
}

void updateDesiredStateOfBoard0() {
    service_bitOperation_setBit(&valueOfOutputBoard0, service_applicationOutputHandler_data.lumierePanneauAvant, 0);
    service_bitOperation_setBit(&valueOfOutputBoard0, service_applicationOutputHandler_data.cylindreVentouseBas, 1);
    service_bitOperation_setBit(&valueOfOutputBoard0, service_applicationOutputHandler_data.cylindreVentouseHaut, 2);
    service_bitOperation_setBit(&valueOfOutputBoard0, service_applicationOutputHandler_data.vacuumOnSolenoide, 3);
    service_bitOperation_setBit(&valueOfOutputBoard0, service_applicationOutputHandler_data.elevateurPositionBasse, 4);
    service_bitOperation_setBit(&valueOfOutputBoard0, service_applicationOutputHandler_data.elevateurPositionHaute, 5);
    service_bitOperation_setBit(&valueOfOutputBoard0, service_applicationOutputHandler_data.poussoirMagasinBlocEntree, 6);
    service_bitOperation_setBit(&valueOfOutputBoard0, service_applicationOutputHandler_data.poussoirMagasinBlocSortie, 7);
}

void updateDesiredStateOfBoard1() {
    service_bitOperation_setBit(&valueOfOutputBoard1, service_applicationOutputHandler_data.ejecteurBlocPositionSortie, 0);
    service_bitOperation_setBit(&valueOfOutputBoard1, service_applicationOutputHandler_data.relaisConvoyeur, 1);
    service_bitOperation_setBit(&valueOfOutputBoard1, service_applicationOutputHandler_data.selectionPosition0, 2);
    service_bitOperation_setBit(&valueOfOutputBoard1, service_applicationOutputHandler_data.selectionPosition1, 3);
    service_bitOperation_setBit(&valueOfOutputBoard1, service_applicationOutputHandler_data.selectionPosition2, 4);
    service_bitOperation_setBit(&valueOfOutputBoard1, service_applicationOutputHandler_data.isEndStageEnabled, 5);
    service_bitOperation_setBit(&valueOfOutputBoard1, service_applicationOutputHandler_data.hasPositionProcessStarted, 6);
}

void setPhysicalOutputs() {
    // pcf #0
    if(previousValueOfOutputBoard0 != valueOfOutputBoard0) {
        interface_pcf8574A_writeOutputByte(PCF8574A_CHIP_ADDRESS_0, valueOfOutputBoard0);
        previousValueOfOutputBoard0 = valueOfOutputBoard0;
    }
    
    // pcf #1
    if(previousValueOfOutputBoard1 != valueOfOutputBoard1) {
        interface_pcf8574A_writeOutputByte(PCF8574A_CHIP_ADDRESS_1, valueOfOutputBoard1);
        previousValueOfOutputBoard1 = valueOfOutputBoard1;
    }
    
    // light column
    service_lightHandler_update(&service_applicationOutputHandler_greenLight);
    service_lightHandler_update(&service_applicationOutputHandler_yellowLight);
    service_lightHandler_update(&service_applicationOutputHandler_redLight);
    
    // step motor
    service_stepperMotor_update(&service_applicationOutputHandler_stepper);
    
    // triac
    service_triac_update(&service_applicationOutputHandler_triac);
    
    // can
    service_can_transmittingUpdate();
}
