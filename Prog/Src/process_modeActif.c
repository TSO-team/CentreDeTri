// process_modeActif.c
// 
// creator: John-William Lebel
// date: 2020-11-20

// inclusions
#include "process_modeActif.h"

#include "process_centreDeTri.h"
#include "service_applicationlnputHandler.h"
#include "service_can.h"

// state struct initialization
service_stateMachine_State process_modeActif_state = {process_modeActif_behaviour,
                                                process_modeActif_actions,
                                                PROCESS_MODEACTIF_AMOUNT_OF_ACTIONS};
// transition array initialization
unsigned int (*process_modeActif_actions[PROCESS_MODEACTIF_AMOUNT_OF_ACTIONS])(void);



// init
void process_modeActif_init() {
    // actions
    process_modeActif_actions[PROCESS_MODEACTIF_RED_BUTTON_PRESSED_ACTION] = process_modeActif_redButtonPressed;
    process_modeActif_actions[PROCESS_MODEACTIF_ERROR_ACTION] = process_modeActif_error;
    
    // state
    process_centreDeTri_states[PROCESS_CENTREDETRI_MODEACTIF_STATE] = process_modeActif_state;
}

// state behaviour
void process_modeActif_behaviour() {
    // notify everybody over can that we're working hard
    service_can_dataToSendCentreDeTri.data.mode = ON;
}

// state transitions
unsigned int process_modeActif_redButtonPressed() {
    unsigned char boutonArret = service_applicationInputHandler_data.boutonArret;
    if(boutonArret) {
        return PROCESS_CENTREDETRI_MODEARRET_STATE;
    }
    // equivalent to pressing red button from can
    if(service_can_dataReceivedPosteDeCommande.data.mode == OFF) {
        service_can_dataReceivedPosteDeCommande.data.mode = UNDEFINED;
        return PROCESS_CENTREDETRI_MODEARRET_STATE;
    }
    
    return process_centreDeTri_stateMachine.currentStateIndex;
}

unsigned int process_modeActif_error() {
    unsigned char errorOccurence = 0;   // unhandled yet
    
    if(errorOccurence) {
        return PROCESS_CENTREDETRI_MODEERREUR_STATE;
    }
    
    return process_centreDeTri_stateMachine.currentStateIndex;
}


