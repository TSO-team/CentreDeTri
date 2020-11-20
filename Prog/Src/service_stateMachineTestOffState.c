// service_stateMachineTestOffState.c
// 
// creator: John-William Lebel
// date: 2020-11-19

// inclusions
// it works "without" this file but fnsdjfnslkfd;llf
//#include "service_stateMachineTestOffState.h"

#include "service_stateMachineTest.h"

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