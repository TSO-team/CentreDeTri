// process_modeErreur.c
// 
// creator: John-William Lebel
// date: 2020-11-20

// inclusions
#include "process_modeErreur.h"

#include "process_centreDeTri.h"
#include "service_applicationlnputHandler.h"
#include "service_can.h"

// state struct initialization
service_stateMachine_State process_modeErreur_state = {process_modeErreur_behaviour,
                                                 process_modeErreur_actions,
                                                 PROCESS_MODEERREUR_AMOUNT_OF_ACTIONS};
// action array initialization
unsigned int (*process_modeErreur_actions[PROCESS_MODEERREUR_AMOUNT_OF_ACTIONS])(void);



// init
void process_modeErreur_init() {
    // actions
    process_modeErreur_actions[PROCESS_MODEERREUR_BLOCK_ACTION] = process_modeErreur_block;
    
    // state
    process_centreDeTri_states[PROCESS_CENTREDETRI_MODEERREUR_STATE] = process_modeErreur_state;
}

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

