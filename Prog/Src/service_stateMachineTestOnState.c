// service_stateMachineTestOnState.c
// 
// creator: John-William Lebel
// date: 2020-11-19

// inclusions
#include "service_stateMachineTestOnState.h"

#include "service_stateMachineTest.h"

// state struct initialization
service_stateMachine_State ledOn = {turnOnLed, stateTransitionsForOnState, AMOUNT_OF_STATE_TRANSITIONS_FOR_ON_STATE};
// transition array initialization
unsigned int (*stateTransitionsForOnState[AMOUNT_OF_STATE_TRANSITIONS_FOR_ON_STATE])(void);

// state behaviour
void turnOnLed() {
    // haha piloteTIO1 go brr (gawd it's not working who did thi- ah it's me...)
}

// state transitions
unsigned int isOnTimeElapsed() {
    static unsigned int onCounter = 0;
    
    onCounter++;
    if(onCounter < 1000) {
        return stateMachine.currentStateIndex;
    }
    
    onCounter = 0;
    return LED_OFF_STATE_INDEX;
}