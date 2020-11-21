// service_stateMachineTestOffState.c
// 
// creator: John-William Lebel
// date: 2020-11-19

// inclusions
#include "service_stateMachineTestOffState.h"

#include "service_stateMachineTest.h"

// state struct initialization
service_stateMachine_State ledOff = {turnOffLed, stateTransitionsForOffState, AMOUNT_OF_STATE_TRANSITIONS_FOR_OFF_STATE};
// transition array initialization
unsigned int (*stateTransitionsForOffState[AMOUNT_OF_STATE_TRANSITIONS_FOR_OFF_STATE])(void);

// state behaviour
void turnOffLed() {
    
}

// state transitions
unsigned int isOffTimeElapsed() {
    static unsigned int offCounter = 0;
    
    offCounter++;
    if(offCounter < 1000) {
        return stateMachine.currentStateIndex;
    }
    
    offCounter = 0;
    return LED_ON_STATE_INDEX;
}