// process_modeInit.h
// 
// creator: John-William Lebel
// date: 2020-11-20

#ifndef PROCESS_MODEINIT_H
#define PROCESS_MODEINIT_H

// inclusions
#include "service_stateMachine.h"

// state transition index definition
#define PROCESS_MODEINIT_AMOUNT_OF_ACTIONS 1
#define PROCESS_MODEINIT_GO_TO_MODE_ATTENTE_ACTION 0

// state struct initialization
extern service_stateMachine_State process_modeInit_state;
// transition array initialization
extern unsigned int (*process_modeInit_actions[PROCESS_MODEINIT_AMOUNT_OF_ACTIONS])(void);

// init
void process_modeInit_init();
// behaviour prototype
void process_modeInit_behaviour();
// action prototypes
unsigned int process_modeInit_goToModeAttente();

#endif