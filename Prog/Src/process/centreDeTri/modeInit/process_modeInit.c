// process_modeInit.c
// 
// creator: John-William Lebel
// date: 2020-11-20

// inclusions
#include "process_modeInit.h"

#include "../../../service/stateMachine/service_stateMachine.h"
#include "../process_centreDeTri.h"
#include "../../../service/appInput/service_applicationInputHandler.h"
#include "../../../service/communication/service_can.h"

// behaviour
void process_modeInit_behaviour() {
    // notify everybody over can that we're in waiting mode
    // (it's the next mode we're gonna be at the next update call, so it's not exactly wrong...
    // It's done this way because the "init state" is questionnably a state at all in the defined state machine...
    // Plus, we only spend one interrupt call in this state, so I don't think
    // it's worth changing the can protocol for this)
    service_can_dataToSendCentreDeTri.data.mode = WAIT;
    
    // init centre de tri variables and stuff here
    // init stuff...
}

// actions
unsigned int process_modeInit_goToModeAttente() {
    return PROCESS_CENTREDETRI_MODEATTENTE_STATE;
}

// init
void process_modeInit_init() {
    process_centreDeTri_states[PROCESS_CENTREDETRI_MODEINIT_STATE] = (service_stateMachine_State) {
        process_modeInit_behaviour,
        (unsigned int(*[])(void)) {
            process_modeInit_goToModeAttente
        },
        PROCESS_MODEINIT_AMOUNT_OF_ACTIONS
    };
}
