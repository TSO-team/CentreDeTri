// processCentreDeTri.c
// changes: 2020-11-19, John-William Lebel, creation

#include "process_centreDeTri.h"
#include "serviceBaseDeTemps.h"

void process_centreDeTri_init() {
    serviceBaseDeTemps_execute[SERVICEBASEDETEMPS_PHASE_DATA_PROCESSING]
        = process_centreDeTri_modeActif;
}

void process_centreDeTri_modeAttente() {
    
}

void process_centreDeTri_modeActif() {
    
}

void process_centreDeTri_modeArret() {
    
}

void process_centreDeTri_modeTest() {
    
}

void process_centreDeTri_modeErreur() {
    
}
