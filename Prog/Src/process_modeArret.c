// process_modeArret.c
// 
// creator: John-William Lebel
// date: 2020-11-20

// inclusions
#include "process_modeArret.h"

#include "process_centreDeTri.h"
#include "service_applicationlnputHandler.h"
#include "service_can.h"

// state struct initialization
service_stateMachine_State process_modeArret_state = {process_modeArret_behaviour,
                                                process_modeArret_actions,
                                                PROCESS_MODEARRET_AMOUNT_OF_ACTIONS};
// transition array initialization
unsigned int (*process_modeArret_actions[PROCESS_MODEARRET_AMOUNT_OF_ACTIONS])(void);



// init
void process_modeArret_init() {
    // actions
    process_modeArret_actions[PROCESS_MODEARRET_GREEN_BUTTON_PRESSED_ACTION] = process_modeArret_greenButtonPressed;
    process_modeArret_actions[PROCESS_MODEARRET_ERROR_ACTION] = process_modeArret_error;
    
    // state
    process_centreDeTri_states[PROCESS_CENTREDETRI_MODEARRET_STATE] = process_modeArret_state;
}

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
    if(service_can_dataReceivedPosteDeCommande.data.mode == ON) {
        service_can_dataReceivedPosteDeCommande.data.mode = UNDEFINED;
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

