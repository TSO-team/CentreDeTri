// service_stateMachine.c
// 
// creator: John-William Lebel
// date: 2020-11-19

#include "service_stateMachine.h"

void update(StateMachine* stateMachine) {
    // variable to help handle state transitions
    static unsigned int nextStateIndex;
    
    // get the current transitionnable state
    // ("transitionnable state" meaning "the current state that we're at, and that
    // can change to another state in the state machine by using transitions")
    TransitionnableState currentState
        = stateMachine->transitionnableStates[stateMachine->currentStateIndex];
    
    // execute the current state behaviour
    currentState.stateBehaviour();
    
    // handle any occuring state transition.
    // even if there are 2 or more transitions at the same time, we only execute
    // the first one that we catch
    for(unsigned int i = 0; i < currentState.amountOfTransitions; i++) {
        nextStateIndex = currentState.stateTransitions[i]();
        if(stateMachine->currentStateIndex != nextStateIndex) {
            stateMachine->currentStateIndex = nextStateIndex;
            return;
        }
    }
}