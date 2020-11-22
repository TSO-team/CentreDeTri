// service_lightHandlerBlinkOff.c
// 
// creation: 2020-11-21, John-William Lebel

#include "service_lightHandlerBlinkOff.h"

#include "main.h"

#include "service_stateMachine.h"
#include "service_lightHandler.h"

// behaviour
void service_lightHandlerBlinkOff_behaviour() {
    service_lightHandler_currentlyHandledLight->lightOutput(0);
}

// actions
unsigned int service_lightHandlerBlinkOff_mode_equals_ON() {
    unsigned char* lightMode = &service_lightHandler_currentlyHandledLight->mode;
    
    if(*lightMode != SERVICE_LIGHTHANDLER_ON) {
        return service_lightHandler_stateMachine.currentStateIndex;
    }
    
    return SERVICE_LIGHTHANDLER_ON_STATE;
}

unsigned int service_lightHandlerBlinkOff_amountOfTimeThatLightDidntBlink_biggerThan_timeToStayOffWhenBlinking() {
    float* time = &service_lightHandler_currentlyHandledLight->amountOfTimeThatLightDidntBlink;
    unsigned int* threshold = &service_lightHandler_currentlyHandledLight->timeToStayOffWhenBlinking;
    
    if(*time <= *threshold) {
        return service_lightHandler_stateMachine.currentStateIndex;
    }
    
    *time = 0;
    return SERVICE_LIGHTHANDLER_BLINKON_STATE;
}

// constructor or somemthing
service_stateMachine_State service_lightHandlerBlinkOff_getState() {
    return (service_stateMachine_State) {
        service_lightHandlerBlinkOff_behaviour,
        (unsigned int (*[])(void)) {
            service_lightHandlerBlinkOff_mode_equals_ON,
            service_lightHandlerBlinkOff_amountOfTimeThatLightDidntBlink_biggerThan_timeToStayOffWhenBlinking
        },
        SERVICE_LIGHTHANDLERBLINKOFF_AMOUNT_OF_ACTIONS
    };
}