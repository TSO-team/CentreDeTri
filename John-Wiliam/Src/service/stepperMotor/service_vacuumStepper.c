// service_vacuumStepper:
// Historique: 
// 2020-10-22, John-William Lebel, creation

#include "service_vacuumStepper.h"

#include "main.h"

#include "../appInput/service_applicationInputHandler.h"
#include "../appOutput/service_applicationOutputHandler.h"

// initialization
void service_vacuumStepper_init() {
    // y'a tu de l'init à faire?
}

void service_vacuumStepper_update(service_vacuumStepper_Stepper* stepper) {
    // les inputs qu'on a!
    unsigned char isReadyForOperation = service_applicationInputHandler_data.isReadyForOperation;
    unsigned char isDefaultMotionComplete = service_applicationInputHandler_data.isDefaultMotionComplete;
    unsigned char isDefaultAckStart = service_applicationInputHandler_data.isDefaultAckStart;
    unsigned char hasDefaultError = service_applicationInputHandler_data.hasDefaultError;
    
    // pis ça c'est les outputs!
    service_applicationOutputHandler_data.selectionPosition0;
    service_applicationOutputHandler_data.selectionPosition1;
    service_applicationOutputHandler_data.selectionPosition2;
    service_applicationOutputHandler_data.isEndStageEnabled;
    service_applicationOutputHandler_data.hasPositionProcessStarted;
}