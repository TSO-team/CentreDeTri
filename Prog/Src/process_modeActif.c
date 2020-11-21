// process_modeActif.c
// 
// creator: John-William Lebel
// date: 2020-11-20

// inclusions
#include "process_modeActif.h"

#include "service_stateMachine.h"
#include "process_centreDeTri.h"
#include "service_applicationInputHandler.h"
#include "service_can.h"

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

// init
void process_modeActif_init() {
    process_centreDeTri_states[PROCESS_CENTREDETRI_MODEARRET_STATE] = (service_stateMachine_State) {
        process_modeActif_behaviour,
        (unsigned int(*[])(void)) {
            process_modeActif_redButtonPressed,
            process_modeActif_error
        },
        PROCESS_MODEACTIF_AMOUNT_OF_ACTIONS
    };
}


