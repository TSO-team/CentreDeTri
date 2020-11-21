// service_stateMachineTest.c
// 
// creator: John-William Lebel
// date: 2020-11-19

#include "service_stateMachineTest.h"

// why
#include "main.h"

#include "service_stateMachine.h"

#include "service_stateMachineTestOnState.h"
#include "service_stateMachineTestOffState.h"

// private variables
service_stateMachine_State states[AMOUNT_OF_STATES];

// public variables
service_stateMachine_StateMachine stateMachine = {INITIAL_STATE_INDEX, states};

// public functions
void service_stateMachineTest_init() {
    // description state 1
    states[LED_ON_STATE_INDEX] = ledOn;
    stateTransitionsForOnState[IS_ON_TIME_ELAPSED_TRANSITION_INDEX] = isOnTimeElapsed;
    
    // description state 2
    states[LED_OFF_STATE_INDEX] = ledOff;
    stateTransitionsForOffState[IS_OFF_TIME_ELAPSED_TRANSITION_INDEX] = isOffTimeElapsed;
}

