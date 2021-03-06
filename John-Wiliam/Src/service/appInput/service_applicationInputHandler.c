// service_applicationInputHandler.c
// 
// creator: John-William Lebel et Philippe Lemoine
// date: 2020-11-18
// 2020-11-21, John-William Lebel, removed a lot of unused bitfields

#include "service_applicationInputHandler.h"

#include "main.h"

#include "../../driver/onBoardButton/driver_testButton.h"

#include "../baseDeTemps/serviceBaseDeTemps.h"
#include "../communication/service_can.h"
#include "../button/service_buttonUtils.h"
#include "../math/service_bitOperation.h"

#include "../../interface/carteIO/interface_pcf8574A.h"
#include "../../interface/carteIO/interface_mcp3021.h"

unsigned char valueOfInputBoard0;
unsigned char valueOfInputBoard1;
unsigned char valueOfInputBoard2;
unsigned char valueOfAdc;
service_buttonUtils_Button boutonDepartState;
service_buttonUtils_Button boutonArretState;
service_buttonUtils_Button boutonTestState;

service_applicationInputHandler_Data service_applicationInputHandler_data;

void gatherData();
void updateKnowledgeOfBoard0();
void updateKnowledgeOfBoard1();
void updateKnowledgeOfBoard2();
void updateKnowledgeOfAdc();
void updateKnowledgeOfCan();

void service_applicationInputHandler_init() {
    valueOfInputBoard0 = 0;
    valueOfInputBoard1 = 0;
    valueOfInputBoard2 = 0;
    valueOfAdc = 0;
    
    service_buttonUtils_init(&boutonDepartState);
    service_buttonUtils_init(&boutonArretState);
    service_buttonUtils_init(&boutonTestState);
    
    serviceBaseDeTemps_execute[SERVICEBASEDETEMPS_PHASE_UPDATE_APP_INPUTS]
        = service_applicationInputHandler_update;
}

void service_applicationInputHandler_update() {
    gatherData();
    
    updateKnowledgeOfBoard0();
    updateKnowledgeOfBoard1();
    updateKnowledgeOfBoard2();
    updateKnowledgeOfAdc();
    updateKnowledgeOfCan();
    // please refer to the connection table and schematic in the documentation for further info on physical connections
}

void gatherData() {
    valueOfInputBoard0 = interface_pcf8574A_readInputByte(PCF8574A_CHIP_ADDRESS_2);
    valueOfInputBoard1 = interface_pcf8574A_readInputByte(PCF8574A_CHIP_ADDRESS_3);
    valueOfInputBoard2 = interface_pcf8574A_readInputByte(PCF8574A_CHIP_ADDRESS_4);
    valueOfAdc = interface_mcp3021_readInputByte();
}

void updateKnowledgeOfBoard0() {
    service_applicationInputHandler_data.poussoirMagasinBlocPositionEntree = service_bitOperation_isolateBit(valueOfInputBoard0, 0);
    service_applicationInputHandler_data.poussoirMagasinBlocPositionSortie = service_bitOperation_isolateBit(valueOfInputBoard0, 1);
    service_applicationInputHandler_data.detecteurOptiqueTypeBloc = service_bitOperation_isolateBit(valueOfInputBoard0, 2);
    service_applicationInputHandler_data.detecteurOptiqueBlocChute = service_bitOperation_isolateBit(valueOfInputBoard0, 3);
    
    service_buttonUtils_updateInternalValues(&boutonDepartState, service_bitOperation_isolateBit(valueOfInputBoard0, 4));
    service_applicationInputHandler_data.boutonDepart = service_buttonUtils_clicked(&boutonDepartState);
    
    service_buttonUtils_updateInternalValues(&boutonArretState, service_bitOperation_isolateBit(valueOfInputBoard0, 5));
    service_applicationInputHandler_data.boutonArret = service_buttonUtils_clicked(&boutonArretState);
    
    service_buttonUtils_updateInternalValues(&boutonTestState, driver_testButton_read());
    service_applicationInputHandler_data.boutonTest = service_buttonUtils_clicked(&boutonTestState);
    
    service_applicationInputHandler_data.indicationPressionVentouse = service_bitOperation_isolateBit(valueOfInputBoard0, 6);
}

void updateKnowledgeOfBoard1() {
    service_applicationInputHandler_data.cylindreVentouseHaut = service_bitOperation_isolateBit(valueOfInputBoard1, 0);
    service_applicationInputHandler_data.cylindreVentouseBas = service_bitOperation_isolateBit(valueOfInputBoard1, 1);
    service_applicationInputHandler_data.detecteurMagnetiqueTypeBloc = service_bitOperation_isolateBit(valueOfInputBoard1, 2);
    service_applicationInputHandler_data.detecteurCapacitifTypeBloc = service_bitOperation_isolateBit(valueOfInputBoard1, 3);
    service_applicationInputHandler_data.ejecteurBlocPositionEntree = service_bitOperation_isolateBit(valueOfInputBoard1, 4);
    service_applicationInputHandler_data.ejecteurBlocPositionSortie = service_bitOperation_isolateBit(valueOfInputBoard1, 5);
    service_applicationInputHandler_data.elevateurBas = service_bitOperation_isolateBit(valueOfInputBoard1, 6);
    service_applicationInputHandler_data.elevateurHaut = service_bitOperation_isolateBit(valueOfInputBoard1, 7);
}

void updateKnowledgeOfBoard2() {
    service_applicationInputHandler_data.isReadyForOperation = service_bitOperation_isolateBit(valueOfInputBoard2, 0);
    service_applicationInputHandler_data.isDefaultMotionComplete = service_bitOperation_isolateBit(valueOfInputBoard2, 1);
    service_applicationInputHandler_data.isDefaultAckStart = service_bitOperation_isolateBit(valueOfInputBoard2, 2);
    service_applicationInputHandler_data.hasDefaultError = service_bitOperation_isolateBit(valueOfInputBoard2, 3);
}

void updateKnowledgeOfAdc() {
    service_applicationInputHandler_data.detecteurHauteurBloc = valueOfAdc;
}

void updateKnowledgeOfCan() {
    service_can_receivingUpdate();
}