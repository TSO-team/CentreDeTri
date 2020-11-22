// process_modeAttente.c
// 
// creator: John-William Lebel
// date: 2020-11-20

// inclusions
#include "process_modeAttente.h"

#include "../../../service/stateMachine/service_stateMachine.h"
#include "../process_centreDeTri.h"
#include "../../../service/appInput/service_applicationInputHandler.h"
#include "../../../service/communication/service_can.h"

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
    unsigned char canMode = service_can_dataReceivedPosteDeCommande.data.mode;
    if(canMode == ON) {
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
    unsigned char canMode = service_can_dataReceivedPosteDeCommande.data.mode;
    if(canMode == OFF) {
        return PROCESS_CENTREDETRI_MODEARRET_STATE;
    }
    
    return process_centreDeTri_stateMachine.currentStateIndex;
}

unsigned int process_modeAttente_blueButtonPressed() {
    unsigned char boutonTest = service_applicationInputHandler_data.boutonTest;
    if(boutonTest) {
        return PROCESS_CENTREDETRI_MODETEST_STATE;
    }
    
    // equivalent to pressing blue button from can
    unsigned char canMode = service_can_dataReceivedPosteDeCommande.data.mode;
    if(canMode == TEST) {
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

// init
void process_modeAttente_init() {
    process_centreDeTri_states[PROCESS_CENTREDETRI_MODEATTENTE_STATE] = (service_stateMachine_State) {
        process_modeAttente_behaviour,
        (unsigned int(*[])(void)) {
            process_modeAttente_greenButtonPressed,
            process_modeAttente_redButtonPressed,
            process_modeAttente_blueButtonPressed,
            process_modeAttente_error
        },
        PROCESS_MODEATTENTE_AMOUNT_OF_ACTIONS
    };
}
