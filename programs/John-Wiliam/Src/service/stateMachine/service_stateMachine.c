// service_stateMachine.c
// 
// date: 2020-11-19, John-William Lebel, creation
// date: 2020-11-21, John-William Lebel, changed the names of some elements for clarity

#include "service_stateMachine.h"

void service_stateMachine_update(service_stateMachine_StateMachine* stateMachine) {
    // variable to help handle state transitions
    static unsigned int nextStateIndex;
    
    // get the current state
    service_stateMachine_State currentState
        = stateMachine->states[stateMachine->currentStateIndex];
    
    // execute the current state behaviour
    currentState.behaviour();
    
    // handle any occuring "actions". ("actions" in state machines are the arrows on state diagrams.
    // They represent transitions between states)
    // even if there are 2 or more actions that occur at the same time, we only execute
    // the first one that we catch
    for(unsigned int i = 0; i < currentState.amountOfActions; i++) {
        nextStateIndex = currentState.actions[i]();
        if(stateMachine->currentStateIndex != nextStateIndex) {
            stateMachine->currentStateIndex = nextStateIndex;
            return;
        }
    }
}