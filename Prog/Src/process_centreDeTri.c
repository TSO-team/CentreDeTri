// processCentreDeTri.c
// changes: 2020-11-19, John-William Lebel, creation

#include "process_centreDeTri.h"

#include "main.h"

#include "serviceBaseDeTemps.h"
#include "service_stateMachine.h"

#include "process_modeInit.h"
#include "process_modeAttente.h"
#include "process_modeActif.h"
#include "process_modeArret.h"
#include "process_modeTest.h"
#include "process_modeErreur.h"

// private function prototypes
void process_centreDeTri_update();

// public variables (extern)
service_stateMachine_State process_centreDeTri_states[PROCESS_CENTREDETRI_AMOUNT_OF_STATES];
service_stateMachine_StateMachine process_centreDeTri_stateMachine = {PROCESS_CENTREDETRI_INITIAL_STATE, process_centreDeTri_states};

void process_centreDeTri_init() {
    process_modeInit_init();
    process_modeAttente_init();
    process_modeActif_init();
    process_modeArret_init();
    process_modeTest_init();
    process_modeErreur_init();
    
    serviceBaseDeTemps_execute[SERVICEBASEDETEMPS_PHASE_DATA_PROCESSING]
        = process_centreDeTri_update;
}

void process_centreDeTri_update() {
    service_stateMachine_update(&process_centreDeTri_stateMachine);
}
