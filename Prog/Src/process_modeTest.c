// process_modeTest.c
// 
// creator: John-William Lebel
// date: 2020-11-20

// inclusions
#include "process_modeTest.h"

#include "process_centreDeTri.h"

#include "service_stateMachine.h"
#include "service_applicationlnputHandler.h"
#include "service_can.h"

// state struct initialization
service_stateMachine_State process_modeTest_state = {process_modeTest_behaviour,
                                                     process_modeTest_actions,
                                                     PROCESS_MODETEST_AMOUNT_OF_ACTIONS};
// action array initialization
unsigned int (*process_modeTest_actions[PROCESS_MODETEST_AMOUNT_OF_ACTIONS])(void);


// init
void process_modeTest_init() {
    // actions
    process_modeTest_actions[PROCESS_MODETEST_RED_BUTTON_PRESSED_ACTION] = process_modeTest_redButtonPressed;
    process_modeTest_actions[PROCESS_MODETEST_ERROR_ACTION] = process_modeTest_error;
    
    // state
    process_centreDeTri_states[PROCESS_CENTREDETRI_MODETEST_STATE] = process_modeTest_state;
}

// behaviour
void process_modeTest_behaviour() {
    // notify everybody over can that we're in testing mode
    service_can_dataToSendCentreDeTri.data.mode = TEST;
}

// actions
unsigned int process_modeTest_redButtonPressed() {
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
unsigned int process_modeTest_error() {
    unsigned char errorOccurence = 0;
    
    if(errorOccurence) {
        return PROCESS_CENTREDETRI_MODEERREUR_STATE;
    }
    
    return process_centreDeTri_stateMachine.currentStateIndex;
}
