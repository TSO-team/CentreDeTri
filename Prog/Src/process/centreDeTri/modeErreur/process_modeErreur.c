// process_modeErreur.c
// 
// creator: John-William Lebel
// date: 2020-11-20

// inclusions
#include "process_modeErreur.h"

#include "../../../service/stateMachine/service_stateMachine.h"
#include "../process_centreDeTri.h"
#include "../../../service/appInput/service_applicationInputHandler.h"
#include "../../../service/communication/service_can.h"

// behaviour
void process_modeErreur_behaviour() {
    // notify everybody over can that we've got an error
    service_can_dataToSendCentreDeTri.data.mode = ERROR0;
}

// actions
unsigned int process_modeErreur_block() {
    // stall. We need a hard reset (maybe we need the red power button as an input??)
    unsigned char isReset = 0; // service_applicationInputHandler_data.isPowerOn; // this var doesn't exist yet lol
    
    if(isReset) {
        return PROCESS_CENTREDETRI_MODEINIT_STATE;
    }
    
    return process_centreDeTri_stateMachine.currentStateIndex;
}

// init
void process_modeErreur_init() {
    process_centreDeTri_states[PROCESS_CENTREDETRI_MODEERREUR_STATE] = (service_stateMachine_State) {
        process_modeErreur_behaviour,
        (unsigned int(*[])(void)) {
            process_modeErreur_block
        },
        PROCESS_MODEERREUR_AMOUNT_OF_ACTIONS
    };
}

