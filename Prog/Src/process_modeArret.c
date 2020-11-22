// process_modeArret.c
// 
// creator: John-William Lebel
// date: 2020-11-20

// inclusions
#include "process_modeArret.h"

#include "service_stateMachine.h"
#include "process_centreDeTri.h"
#include "service_applicationInputHandler.h"
#include "service_can.h"

// state behaviour
void process_modeArret_behaviour() {
    // notify everybody over can that we've stopped working
    service_can_dataToSendCentreDeTri.data.mode = OFF;
}

// state transitions
unsigned int process_modeArret_greenButtonPressed() {
    unsigned char boutonDepart = service_applicationInputHandler_data.boutonDepart;
    if(boutonDepart) {
        return PROCESS_CENTREDETRI_MODEATTENTE_STATE;
    }
    // equivalent to pressing green button from can
    if(service_can_dataReceivedPosteDeCommande.data.mode == WAIT) {
        return PROCESS_CENTREDETRI_MODEATTENTE_STATE;
    }
    
    return process_centreDeTri_stateMachine.currentStateIndex;
}

unsigned int process_modeArret_error() {
    unsigned char errorOccurence = 0;
    
    if(errorOccurence) {
        return PROCESS_CENTREDETRI_MODEERREUR_STATE;
    }
    
    return process_centreDeTri_stateMachine.currentStateIndex;
}

// init
void process_modeArret_init() {
    process_centreDeTri_states[PROCESS_CENTREDETRI_MODEARRET_STATE] = (service_stateMachine_State) {
        process_modeArret_behaviour,
        (unsigned int(*[])(void)) {
            process_modeArret_greenButtonPressed,
            process_modeArret_error
        },
        PROCESS_MODEARRET_AMOUNT_OF_ACTIONS
    };
}

