// process_modeAttente.h
// 
// creator: John-William Lebel
// date: 2020-11-20

#ifndef PROCESS_MODEATTENTE_H
#define PROCESS_MODEATTENTE_H

// inclusions
#include "service_stateMachine.h"

// state transition index definition
#define PROCESS_MODEATTENTE_AMOUNT_OF_ACTIONS 4
#define PROCESS_MODEATTENTE_GREEN_BUTTON_PRESSED_ACTION 0
#define PROCESS_MODEATTENTE_RED_BUTTON_PRESSED_ACTION 1
#define PROCESS_MODEATTENTE_BLUE_BUTTON_PRESSED_ACTION 2
#define PROCESS_MODEATTENTE_ERROR_ACTION 3

// state struct initialization
extern service_stateMachine_State process_modeAttente_state;
// transition array initialization
extern unsigned int (*process_modeAttente_actions[PROCESS_MODEATTENTE_AMOUNT_OF_ACTIONS])(void);

// init
void process_modeAttente_init();
// state behaviour prototype
void process_modeAttente_behaviour();
// state transition prototypes
unsigned int process_modeAttente_greenButtonPressed();
unsigned int process_modeAttente_redButtonPressed();
unsigned int process_modeAttente_blueButtonPressed();
unsigned int process_modeAttente_error();

#endif