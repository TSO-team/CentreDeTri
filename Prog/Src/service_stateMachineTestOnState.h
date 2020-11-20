// service_stateMachineTestOnState.h
// 
// creator: John-William Lebel
// date: 2020-11-19

#ifndef SERVICE_STATEMACHINETESTONSTATE_H
#define SERVICE_STATEMACHINETESTONSTATE_H

// inclusions
#include "service_stateMachine.h"

// state behaviour prototype
void turnOnLed();
// state transition prototypes
unsigned int isOnTimeElapsed();/*
unsigned int blablabla();
unsigned int blabliblou();
unsigned int hehehahaBaBiBoBu();*/

// state transition index definition
#define AMOUNT_OF_STATE_TRANSITIONS_FOR_ON_STATE 1
#define IS_ON_TIME_ELAPSED_TRANSITION_INDEX 0

// transition array initialization
unsigned int (*stateTransitionsForOnState[AMOUNT_OF_STATE_TRANSITIONS_FOR_ON_STATE])(void);

// state struct initialization
TransitionnableState ledOn = {turnOnLed, stateTransitionsForOnState, AMOUNT_OF_STATE_TRANSITIONS_FOR_ON_STATE};

#endif