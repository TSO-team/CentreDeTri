// process_modeActif.h
// 
// creator: John-William Lebel
// date: 2020-11-20

#ifndef PROCESS_MODEACTIF_H
#define PROCESS_MODEACTIF_H

// inclusions
#include "service_stateMachine.h"

// state transition index definition
#define PROCESS_MODEACTIF_AMOUNT_OF_ACTIONS 2
#define PROCESS_MODEACTIF_RED_BUTTON_PRESSED_ACTION 0
#define PROCESS_MODEACTIF_ERROR_ACTION 1

// state struct initialization
extern service_stateMachine_State process_modeActif_state;
// transition array initialization
extern unsigned int (*process_modeActif_actions[PROCESS_MODEACTIF_AMOUNT_OF_ACTIONS])(void);

// init
void process_modeActif_init();
// state behaviour prototype
void process_modeActif_behaviour();
// state transition prototypes
unsigned int process_modeActif_redButtonPressed();
unsigned int process_modeActif_error();

#endif