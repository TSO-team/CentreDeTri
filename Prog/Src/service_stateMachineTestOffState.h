// service_stateMachineTestOffState.h
// 
// creator: John-William Lebel
// date: 2020-11-19

#ifndef SERVICE_STATEMACHINETESTOFFSTATE_H
#define SERVICE_STATEMACHINETESTOFFSTATE_H

// inclusions
#include "service_stateMachine.h"

// state transition index definition
#define AMOUNT_OF_STATE_TRANSITIONS_FOR_OFF_STATE 1
#define IS_OFF_TIME_ELAPSED_TRANSITION_INDEX 0

// state struct initialization
extern service_stateMachine_State ledOff;
// transition array initialization
extern unsigned int (*stateTransitionsForOffState[AMOUNT_OF_STATE_TRANSITIONS_FOR_OFF_STATE])(void);

// state behaviour prototype
void turnOffLed();
// state transition prototypes
unsigned int isOffTimeElapsed();/*
unsigned int blablabla();
unsigned int blabliblou();
unsigned int hehehahaBaBiBoBu();*/

#endif