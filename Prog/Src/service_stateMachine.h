// service_stateMachine.h
// 
// creator: John-William Lebel
// date: 2020-11-19

#ifndef SERVICE_STATEMACHINE_H
#define SERVICE_STATEMACHINE_H

typedef struct {
    void (*stateBehaviour)(void);
    unsigned int (**stateTransitions)(void);
    unsigned int amountOfTransitions;
} TransitionnableState;

typedef struct {
    unsigned int currentStateIndex;
    TransitionnableState* transitionnableStates;
} StateMachine;

void update(StateMachine* stateMachine);

#endif