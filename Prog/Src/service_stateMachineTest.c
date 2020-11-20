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
TransitionnableState transitionnableStates[AMOUNT_OF_STATES];

// public variables
StateMachine stateMachine = {INITIAL_STATE_INDEX, transitionnableStates};

// public functions
void service_stateMachineTest_init() {
    stateTransitionsForOnState[IS_ON_TIME_ELAPSED_TRANSITION_INDEX] = isOnTimeElapsed;
    stateTransitionsForOffState[IS_OFF_TIME_ELAPSED_TRANSITION_INDEX] = isOffTimeElapsed;
    transitionnableStates[LED_ON_STATE_INDEX] = ledOn;
    transitionnableStates[LED_OFF_STATE_INDEX] = ledOff;
}

