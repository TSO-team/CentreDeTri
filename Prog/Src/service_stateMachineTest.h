// service_stateMachineTest.h
// 
// creator: John-William Lebel
// date: 2020-11-19

#ifndef SERVICE_STATEMACHINETEST_H
#define SERVICE_STATEMACHINETEST_H

// inclusions
#include "service_stateMachine.h"

// state index definitions
#define AMOUNT_OF_STATES 2
#define LED_ON_STATE_INDEX 0
#define LED_OFF_STATE_INDEX 1

// initial state index definition
#define INITIAL_STATE_INDEX LED_ON_STATE_INDEX

// variables defined in the .c
extern StateMachine stateMachine;

// public functions
void service_stateMachineTest_init();

#endif