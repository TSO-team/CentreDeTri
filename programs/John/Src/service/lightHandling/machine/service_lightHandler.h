// service_lightHandler.h
//
// creation: 2020-11-21, John-William Lebel

// to use this light handler, you need to:
// 1) call the "service_lightHandler_init()" function once;
//
// 2) instantiate the lights with: 
// service_lightHandler_Light myLight
// = {  MODE,
//      0,
//      ON_TIME_WHEN_BLINKING,
//      OFF_TIME_WHEN_BLINKING,
//      void (*)(unsigned char) // -> your function that can control lights physically
//   };
//
// 3) call the "service_lightHandler_update(&myLight)" func regularly
// this implementation uses the main.h define "TEMPS_ECOULE_EN_MS_ENTRE_CHAQUE_INTERRUPTION"
// if you don't have it, replace TEMPS_ECOULE_EN_MS_ENTRE_CHAQUE_INTERRUPTION in the right code section
// with the amount of time seperating each call of the "service_lightHandler_update(&myLight)" func. 
// 
// 4) once you're ready to change the light mode, you do: myLight.mode = SERVICE_LIGHTHANDLER_ON or SERVICE_LIGHTHANDLER_OFF or SERVICE_LIGHTHANDLER_BLINK
// 
// I'm doing it this way because I don't know how to make
// private variables using structures in C, so don't mind me...

#ifndef SERVICE_LIGHTHANDLER_H
#define SERVICE_LIGHTHANDLER_H

#include "../../stateMachine/service_stateMachine.h"

#define SERVICE_LIGHTHANDLER_AMOUNT_OF_STATES 4
#define SERVICE_LIGHTHANDLER_ON_STATE 0
#define SERVICE_LIGHTHANDLER_OFF_STATE 1
#define SERVICE_LIGHTHANDLER_BLINKON_STATE 2
#define SERVICE_LIGHTHANDLER_BLINKOFF_STATE 3

typedef enum {
    SERVICE_LIGHTHANDLER_ON,
    SERVICE_LIGHTHANDLER_OFF,
    SERVICE_LIGHTHANDLER_BLINK,
} service_lightHandler_Mode;

typedef struct {
    unsigned char mode;
    float amountOfTimeThatLightDidntBlink;
    unsigned int timeToStayOnWhenBlinking;
    unsigned int timeToStayOffWhenBlinking;
    void (*lightOutput)(unsigned char lightValue);
} service_lightHandler_Light;

// light state
extern service_lightHandler_Light* service_lightHandler_currentlyHandledLight;

// states
extern service_stateMachine_State service_lightHandler_states[SERVICE_LIGHTHANDLER_AMOUNT_OF_STATES];
// state machine
extern service_stateMachine_StateMachine service_lightHandler_stateMachine;

void service_lightHandler_init();
void service_lightHandler_update(service_lightHandler_Light* light);

#endif
 