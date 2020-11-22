// service_lightHandlerOff.c
// 
// creation: 2020-11-21, John-William Lebel

#include "service_lightHandlerOff.h"

#include "main.h"

#include "../../../stateMachine/service_stateMachine.h"
#include "../../machine/service_lightHandler.h"

// behaviour
void service_lightHandlerOff_behaviour() {
    service_lightHandler_currentlyHandledLight->lightOutput(0);
}

// actions
unsigned int service_lightHandlerOff_mode_equals_BLINK() {
    unsigned char* lightMode = &service_lightHandler_currentlyHandledLight->mode;
    
    if(*lightMode != SERVICE_LIGHTHANDLER_BLINK) {
        return service_lightHandler_stateMachine.currentStateIndex;
    }
    
    return SERVICE_LIGHTHANDLER_BLINKON_STATE;
}

unsigned int service_lightHandlerOff_mode_equals_ON() {
    unsigned char* lightMode = &service_lightHandler_currentlyHandledLight->mode;
    
    if(*lightMode != SERVICE_LIGHTHANDLER_ON) {
        return service_lightHandler_stateMachine.currentStateIndex;
    }
    
    return SERVICE_LIGHTHANDLER_ON_STATE;
}

// constructor or something
service_stateMachine_State service_lightHandlerOff_getState() {
    return (service_stateMachine_State) {
        service_lightHandlerOff_behaviour,
        (unsigned int (*[])(void)) {
            service_lightHandlerOff_mode_equals_BLINK,
            service_lightHandlerOff_mode_equals_ON
        },
        SERVICE_LIGHTHANDLEROFF_AMOUNT_OF_ACTIONS
    };
}