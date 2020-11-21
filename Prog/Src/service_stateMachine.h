// service_stateMachine.h
// 
// date: 2020-11-19, John-William Lebel, creation
// date: 2020-11-21, John-William Lebel, changed the names of some elements for clarity

#ifndef SERVICE_STATEMACHINE_H
#define SERVICE_STATEMACHINE_H

typedef struct {
    void (*behaviour)(void);
    unsigned int (**actions)(void);
    unsigned int amountOfActions;
} service_stateMachine_State;

typedef struct {
    unsigned int currentStateIndex;
    service_stateMachine_State* states;
} service_stateMachine_StateMachine;

void service_stateMachine_update(service_stateMachine_StateMachine* stateMachine);

#endif