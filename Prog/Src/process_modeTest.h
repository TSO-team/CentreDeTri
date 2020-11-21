// process_modeTest.h
// 
// creator: John-William Lebel
// date: 2020-11-20

#ifndef PROCESS_MODETEST_H
#define PROCESS_MODETEST_H

// inclusions
#include "service_stateMachine.h"

// action definitions
#define PROCESS_MODETEST_AMOUNT_OF_ACTIONS 2
#define PROCESS_MODETEST_RED_BUTTON_PRESSED_ACTION 0
#define PROCESS_MODETEST_ERROR_ACTION 1

// state struct initialization
extern service_stateMachine_State process_modeTest_state;
// action array initialization
extern unsigned int (*process_modeTest_actions[PROCESS_MODETEST_AMOUNT_OF_ACTIONS])(void);

// init
void process_modeTest_init();
// behaviour prototype
void process_modeTest_behaviour();
// action prototypes
unsigned int process_modeTest_redButtonPressed();
unsigned int process_modeTest_error();

#endif