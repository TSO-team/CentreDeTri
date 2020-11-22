// service_applicationOutputHandler.h
// 
// interface for the mcp23008 general io expander
// this specific driver defines functions to put the chip's IOs into readonly inputs.
// creator: John-William Lebel
// date: 2020-10-08

#ifndef SERVICE_APPLICATIONOUTPUTHANDLER_H
#define SERVICE_APPLICATIONOUTPUTHANDLER_H

#include "service_stepperMotor.h"
#include "service_lightHandler.h"
#include "service_triac.h"

/* put this in main.h if you're using it and it's not there
#define PCF8574A_CHIP_ADDRESS 0x7A
*/

typedef struct {
    // 8 bits
    unsigned long lumierePanneauAvant: 1,
    cylindreVentouseBas: 1,
    cylindreVentouseHaut: 1,
    vacuumOnSolenoide: 1,
    elevateurPositionBasse: 1,
    elevateurPositionHaute: 1,
    poussoirMagasinBlocEntree: 1,
    poussoirMagasinBlocSortie: 1,
    
    // 7 bits
    ejecteurBlocPositionSortie: 1,
    relaisConvoyeur: 1,
    selectionPosition0: 1,
    selectionPosition1: 1,
    selectionPosition2: 1,
    isEndStageEnabled: 1,
    hasPositionProcessStarted: 1,
    
    // 10 bit
    vide: 17;
    
    // 32 bits
    long stepperDestination;
    
} service_applicationOutputHandler_Data;

// unhandled data! Must empty this thing
// it works, but it needs additionnal services. 
// the goal is to put everything in usable structs
extern service_applicationOutputHandler_Data service_applicationOutputHandler_data;

// stepper motor position and destination handling
extern service_stepperMotor_Stepper service_applicationOutputHandler_stepper;

// light on, off, and blink handling
extern service_lightHandler_Light service_applicationOutputHandler_greenLight;
extern service_lightHandler_Light service_applicationOutputHandler_yellowLight;
extern service_lightHandler_Light service_applicationOutputHandler_redLight;

extern service_triac_Triac service_applicationOutputHandler_triac;

void service_applicationOutputHandler_init();
void service_applicationOutputHandler_update();

#endif