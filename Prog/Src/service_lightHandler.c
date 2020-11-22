// service_lightHandler.c
// 
// creation: 2020-11-21, John-William Lebel

#include "service_lightHandler.h"

#include "main.h"

#include "service_stateMachine.h"

#include "service_lightHandlerOn.h"
#include "service_lightHandlerOff.h"
#include "service_lightHandlerBlinkOn.h"
#include "service_lightHandlerBlinkOff.h"

// dynamic light data
service_lightHandler_Light* service_lightHandler_currentlyHandledLight;

// state machine declaration
service_stateMachine_State service_lightHandler_states[SERVICE_LIGHTHANDLER_AMOUNT_OF_STATES];
service_stateMachine_StateMachine service_lightHandler_stateMachine;

void service_lightHandler_update(service_lightHandler_Light* light) {
    // this is incredibly wrong, but I didn't find a better way to do this yet.
    // basically, we set a pointer that's going to be used as the variable to
    // provide data to all the states during operation. 
    service_lightHandler_currentlyHandledLight = light;
    
    // update time var
    light->amountOfTimeThatLightDidntBlink += TEMPS_ECOULE_EN_MS_ENTRE_CHAQUE_INTERRUPTION;
    
    // update the state machine
    service_stateMachine_update(&service_lightHandler_stateMachine);
}

void service_lightHandler_init() {
    service_lightHandler_states[SERVICE_LIGHTHANDLER_ON_STATE] = service_lightHandlerOn_getState();
    service_lightHandler_states[SERVICE_LIGHTHANDLER_OFF_STATE] = service_lightHandlerOff_getState();
    service_lightHandler_states[SERVICE_LIGHTHANDLER_BLINKON_STATE] = service_lightHandlerBlinkOn_getState();
    service_lightHandler_states[SERVICE_LIGHTHANDLER_BLINKOFF_STATE] = service_lightHandlerBlinkOff_getState();
    
    service_lightHandler_stateMachine = (service_stateMachine_StateMachine) {
        SERVICE_LIGHTHANDLER_AMOUNT_OF_STATES,
        service_lightHandler_states
    };
}