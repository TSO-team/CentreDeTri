// processCentreDeTri.h
// changes: 2020-11-19, John-William Lebel, creation

#ifndef PROCESS_CENTREDETRI_H
#define PROCESS_CENTREDETRI_H

#include "../../service/stateMachine/service_stateMachine.h"

// state index definitions
#define PROCESS_CENTREDETRI_AMOUNT_OF_STATES 6
#define PROCESS_CENTREDETRI_MODEINIT_STATE 0
#define PROCESS_CENTREDETRI_MODEATTENTE_STATE 1
#define PROCESS_CENTREDETRI_MODEACTIF_STATE 2
#define PROCESS_CENTREDETRI_MODEARRET_STATE 3
#define PROCESS_CENTREDETRI_MODETEST_STATE 4
#define PROCESS_CENTREDETRI_MODEERREUR_STATE 5

// initial state index definition
#define PROCESS_CENTREDETRI_INITIAL_STATE PROCESS_CENTREDETRI_MODEINIT_STATE

// states
extern service_stateMachine_State process_centreDeTri_states[PROCESS_CENTREDETRI_AMOUNT_OF_STATES];
// state machine
extern service_stateMachine_StateMachine process_centreDeTri_stateMachine;

// public functions
void process_centreDeTri_init();

void process_centreDeTri_modeAttente();
void process_centreDeTri_modeActif();
void process_centreDeTri_modeArret();
void process_centreDeTri_modeTest();
void process_centreDeTri_modeErreur();

#endif
