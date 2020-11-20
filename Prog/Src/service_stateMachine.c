// service_stateMachine.c
// 
// creator: John-William Lebel
// date: 2020-11-19

#include "service_stateMachine.h"

void update(StateMachine* stateMachine) {
    // get the current transitionnable state
    TransitionnableState currentState
        = stateMachine->transitionnableStates[stateMachine->currentStateIndex];
    
    // execute its behaviour
    currentState.stateBehaviour();
    
    // handle state transitions
    for(unsigned int i = 0; i < currentState.amountOfTransitions; i++) {
        unsigned int stateIndex = currentState.stateTransitions[i]();
        if(stateMachine->currentStateIndex != stateIndex) {
            stateMachine->currentStateIndex = stateIndex;
            return;
        }
    }
}