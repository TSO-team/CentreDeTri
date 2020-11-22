// service_triac.c
// Historique: 
// 2020-11-21, John-William Lebel, creation

#include "service_triac.h"
#include "main.h"

// initialization
void service_triac_init(service_triac_Triac* triac) {
    triac->timeFromPassageByZero = 0;
    // stupid proof!
    if(triac->dutyCycle > 1) {
        triac->dutyCycle = 1;
    }
    else if(triac->dutyCycle < 0) {
        triac->dutyCycle = 0;
    }
}

void service_triac_update(service_triac_Triac* triac) {
    // get the time we need to activate
    float expectedTimeToActivate = (1-triac->dutyCycle) * SERVICE_TRIAC_EXPECTED_MAX_PULSE_DURATION_IN_MS;
    
    // update the time that passed since last "sync" with the passingByZero function
    triac->timeFromPassageByZero += TEMPS_ECOULE_EN_MS_ENTRE_CHAQUE_INTERRUPTION;
    
    // reset the time if we cross 0V on 120Vac alim
    if(triac->isPassingByZero()) {
        triac->timeFromPassageByZero = 0;
    }
    
    // check if we reached the time to activate the triac
    if(triac->timeFromPassageByZero < expectedTimeToActivate) {
        triac->driveTriac(0);
    }
    else {
        // make sure to activate the triac for about only 1 ms
        //if(triac->timeFromPassageByZero < expectedTimeToActivate + 1) {
      
        // this is a more robust implementation that activates the triac
        // for 1ms, and then deactivates it for 1ms, and repeats this until we pass by zero again
        if(((unsigned char)triac->timeFromPassageByZero) % 2) {
            triac->driveTriac(1);
        }
        else {
            triac->driveTriac(0);
        }
    }
}