// service_lightHandlerOn.c
// 
// creation: 2020-11-21, John-William Lebel

#include "service_lightHandlerOn.h"
#include "main.h"
#include "service_stateMachine.h"
#include "service_lightHandler.h"

// behaviour
void service_lightHandlerOn_behaviour() {
    service_lightHandler_currentlyHandledLight->lightOutput(1);
}

// actions
unsigned int service_lightHandlerOn_mode_equals_BLINK() {
    unsigned char* lightMode = &service_lightHandler_currentlyHandledLight->mode;
    
    if(*lightMode != SERVICE_LIGHTHANDLER_BLINK) {
        return service_lightHandler_stateMachine.currentStateIndex;
    }
    
    return SERVICE_LIGHTHANDLER_BLINKOFF_STATE;
}

unsigned int service_lightHandlerOn_mode_equals_OFF() {
    unsigned char* lightMode = &service_lightHandler_currentlyHandledLight->mode;
    
    if(*lightMode != SERVICE_LIGHTHANDLER_OFF) {
        return service_lightHandler_stateMachine.currentStateIndex;
    }
    
    return SERVICE_LIGHTHANDLER_OFF_STATE;
}

// constructor or somthing
service_stateMachine_State service_lightHandlerOn_getState() {
    return (service_stateMachine_State) {
        service_lightHandlerOn_behaviour,
        (unsigned int (*[])(void)) {
            service_lightHandlerOn_mode_equals_BLINK,
            service_lightHandlerOn_mode_equals_OFF
        },
        SERVICE_LIGHTHANDLERON_AMOUNT_OF_ACTIONS
    };
}