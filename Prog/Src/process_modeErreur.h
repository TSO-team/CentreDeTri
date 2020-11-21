// process_modeErreur.h
// 
// creator: John-William Lebel
// date: 2020-11-20

#ifndef PROCESS_MODEERREUR_H
#define PROCESS_MODEERREUR_H

// inclusions
#include "service_stateMachine.h"

// state transition index definition
#define PROCESS_MODEERREUR_AMOUNT_OF_ACTIONS 1
#define PROCESS_MODEERREUR_BLOCK_ACTION 0

// state struct initialization
extern service_stateMachine_State process_modeErreur_state;
// transition array initialization
extern unsigned int (*process_modeErreur_actions[PROCESS_MODEERREUR_AMOUNT_OF_ACTIONS])(void);

// init
void process_modeErreur_init();
// behaviour prototype
void process_modeErreur_behaviour();
// action prototypes
unsigned int process_modeErreur_block();

#endif