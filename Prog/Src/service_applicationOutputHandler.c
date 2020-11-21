// service_applicationOutputHandler.c
// 
// creator: John-William Lebel et Philippe Lemoine
// date: 2020-11-18

#include "service_applicationOutputHandler.h"
#include "main.h"
#include "serviceBaseDeTemps.h"
#include "service_can.h"
#include "service_bitOperation.h"
#include "interface_pcf8574A.h"
#include "interface_mcp3021.h"
#include "interface_lightColumn.h"
#include "interface_stepperMotor.h"
#include "interface_triac.h"

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

void updateDesiredStateOfBoard0();
void updateDesiredStateOfBoard1();
void updateDesiredStateOfLightColumn();
void updateDesiredStateOfStepMotor();
void updateDesiredStateOfTriac();
void updateDesiredStateOfCanCommunication();
void setPhysicalOutputs();

// public function
void service_applicationOutputHandler_init() {
    valueOfOutputBoard0 = 0;
    previousValueOfOutputBoard0 = 0;
    
    valueOfOutputBoard1 = 0;
    previousValueOfOutputBoard1 = 0;
    
    valueOfLightColumn = 0;
    previousValueOfLightColumn = 0;
    
    stepMotorState = 0;
    previousStepMotorState = 0;
    
    triacState = 0;
    previousTriacState = 0;
    
    serviceBaseDeTemps_execute[SERVICEBASEDETEMPS_PHASE_UPDATE_APP_OUTPUTS]
        = service_applicationOutputHandler_update;
}

void service_applicationOutputHandler_update() {
    updateDesiredStateOfBoard0();
    updateDesiredStateOfBoard1();
    updateDesiredStateOfLightColumn();
    updateDesiredStateOfStepMotor();
    updateDesiredStateOfTriac();
    updateDesiredStateOfCanCommunication();
    
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

void updateDesiredStateOfLightColumn() {
    service_bitOperation_setBit(&valueOfLightColumn, service_applicationOutputHandler_data.greenLightInColumn, 0);
    service_bitOperation_setBit(&valueOfLightColumn, service_applicationOutputHandler_data.yellowLightInColumn, 1);
    service_bitOperation_setBit(&valueOfLightColumn, service_applicationOutputHandler_data.redLightInColumn, 2);
}

void updateDesiredStateOfStepMotor() {
    service_bitOperation_setBit(&stepMotorState, service_applicationOutputHandler_data.stepMotorA1, 0);
    service_bitOperation_setBit(&stepMotorState, service_applicationOutputHandler_data.stepMotorA2, 1);
    service_bitOperation_setBit(&stepMotorState, service_applicationOutputHandler_data.stepMotorB1, 2);
    service_bitOperation_setBit(&stepMotorState, service_applicationOutputHandler_data.stepMotorB2, 3);
}

void updateDesiredStateOfTriac() {
    service_bitOperation_setBit(&triacState, service_applicationOutputHandler_data.triac, 0);
}

void updateDesiredStateOfCanCommunication() {
    service_can_transmittingUpdate();
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
    if(previousValueOfLightColumn != valueOfLightColumn) {
        interface_lightColumn_writeOutputByte(valueOfLightColumn);
        previousValueOfLightColumn = valueOfLightColumn;
    }
    
    // step motor
    if(previousStepMotorState != stepMotorState) {
        interface_stepperMotor_writeOutputByte(stepMotorState);
        previousStepMotorState = stepMotorState;
    }
    
    // triac
    if(previousTriacState != triacState) {
        interface_triac_writeTriacValue(triacState);
        previousTriacState = triacState;
    }
}
