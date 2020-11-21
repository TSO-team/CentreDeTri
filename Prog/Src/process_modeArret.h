// process_modeArret.h
// 
// creator: John-William Lebel
// date: 2020-11-20

#ifndef PROCESS_MODEARRET_H
#define PROCESS_MODEARRET_H

// inclusions
#include "service_stateMachine.h"

// state transition index definition
#define PROCESS_MODEARRET_AMOUNT_OF_ACTIONS 2
#define PROCESS_MODEARRET_GREEN_BUTTON_PRESSED_ACTION 0
#define PROCESS_MODEARRET_ERROR_ACTION 1

// state struct initialization
extern service_stateMachine_State process_modeArret_state;
// transition array initialization
extern unsigned int (*process_modeArret_actions[PROCESS_MODEARRET_AMOUNT_OF_ACTIONS])(void);

// init
void process_modeArret_init();
// state behaviour prototype
void process_modeArret_behaviour();
// state transition prototypes
unsigned int process_modeArret_greenButtonPressed();
unsigned int process_modeArret_error();

#endif