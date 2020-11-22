// service_lightHandlerBlinkOn.c
// 
// creation: 2020-11-21, John-William Lebel

#include "service_lightHandlerBlinkOn.h"

#include "main.h"

#include "../../../stateMachine/service_stateMachine.h"
#include "../../machine/service_lightHandler.h"

// behaviour
void service_lightHandlerBlinkOn_behaviour() {
    service_lightHandler_currentlyHandledLight->lightOutput(1);
}

// actions
unsigned int service_lightHandlerBlinkOn_mode_equals_OFF() {
    unsigned char* lightMode = &service_lightHandler_currentlyHandledLight->mode;
    
    if(*lightMode != SERVICE_LIGHTHANDLER_OFF) {
        return service_lightHandler_stateMachine.currentStateIndex;
    }
    
    return SERVICE_LIGHTHANDLER_OFF_STATE;
}

unsigned int service_lightHandlerBlinkOn_amountOfTimeThatLightDidntBlink_biggerThan_timeToStayOnWhenBlinking() {
    float* time = &service_lightHandler_currentlyHandledLight->amountOfTimeThatLightDidntBlink;
    unsigned int* threshold = &service_lightHandler_currentlyHandledLight->timeToStayOnWhenBlinking;
    
    if(*time <= *threshold) {
        return service_lightHandler_stateMachine.currentStateIndex;
    }
    
    *time = 0;
    return SERVICE_LIGHTHANDLER_BLINKOFF_STATE;
}

// constructor or something
service_stateMachine_State service_lightHandlerBlinkOn_getState() {
    return (service_stateMachine_State) {
        service_lightHandlerBlinkOn_behaviour,
        (unsigned int (*[])(void)) {
            service_lightHandlerBlinkOn_mode_equals_OFF,
            service_lightHandlerBlinkOn_amountOfTimeThatLightDidntBlink_biggerThan_timeToStayOnWhenBlinking
        },
        SERVICE_LIGHTHANDLERBLINKON_AMOUNT_OF_ACTIONS
    };
}