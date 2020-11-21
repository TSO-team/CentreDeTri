// process_modeAttente.c
// 
// creator: John-William Lebel
// date: 2020-11-20

// inclusions
#include "process_modeAttente.h"

#include "process_centreDeTri.h"
#include "service_applicationlnputHandler.h"
#include "service_can.h"

// state struct initialization
service_stateMachine_State process_modeAttente_state = {process_modeAttente_behaviour,
                                                  process_modeAttente_actions,
                                                  PROCESS_MODEATTENTE_AMOUNT_OF_ACTIONS};
// transition array initialization
unsigned int (*process_modeAttente_actions[PROCESS_MODEATTENTE_AMOUNT_OF_ACTIONS])(void);



// init
void process_modeAttente_init() {
    // actions
    process_modeAttente_actions[PROCESS_MODEATTENTE_GREEN_BUTTON_PRESSED_ACTION] = process_modeAttente_greenButtonPressed;
    process_modeAttente_actions[PROCESS_MODEATTENTE_RED_BUTTON_PRESSED_ACTION] = process_modeAttente_redButtonPressed;
    process_modeAttente_actions[PROCESS_MODEATTENTE_BLUE_BUTTON_PRESSED_ACTION] = process_modeAttente_blueButtonPressed;
    process_modeAttente_actions[PROCESS_MODEATTENTE_ERROR_ACTION] = process_modeAttente_error;
    
    // state
    process_centreDeTri_states[PROCESS_CENTREDETRI_MODEATTENTE_STATE] = process_modeAttente_state;
}

// state behaviour
void process_modeAttente_behaviour() {
    // notify everybody over can that we're in waiting mode
    service_can_dataToSendCentreDeTri.data.mode = WAIT;
}

// state transitions
unsigned int process_modeAttente_greenButtonPressed() {
    unsigned char boutonDepart = service_applicationInputHandler_data.boutonDepart;
    if(boutonDepart) {
        return PROCESS_CENTREDETRI_MODEACTIF_STATE;
    }
    // equivalent to pressing green button from can
    if(service_can_dataReceivedPosteDeCommande.data.mode == ON) {
        service_can_dataReceivedPosteDeCommande.data.mode = UNDEFINED;
        return PROCESS_CENTREDETRI_MODEACTIF_STATE;
    }
    
    return process_centreDeTri_stateMachine.currentStateIndex;
}

unsigned int process_modeAttente_redButtonPressed() {
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

// ????????
unsigned int process_modeAttente_blueButtonPressed() {
    unsigned char boutonTest = 0; // service_applicationInputHandler_data.boutonTest;
    if(boutonTest) {
        return PROCESS_CENTREDETRI_MODETEST_STATE;
    }
    
    // equivalent to pressing blue button from can
    if(service_can_dataReceivedPosteDeCommande.data.mode == TEST) {
        service_can_dataReceivedPosteDeCommande.data.mode = UNDEFINED;
        return PROCESS_CENTREDETRI_MODETEST_STATE;
    }
    
    return process_centreDeTri_stateMachine.currentStateIndex;
}

unsigned int process_modeAttente_error() {
    unsigned char errorOccurence = 0;
    
    if(errorOccurence) {
        return PROCESS_CENTREDETRI_MODEERREUR_STATE;
    }
    
    return process_centreDeTri_stateMachine.currentStateIndex;
}