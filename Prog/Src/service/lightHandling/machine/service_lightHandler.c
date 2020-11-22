// service_lightHandler.c
// 
// creation: 2020-11-21, John-William Lebel

#include "service_lightHandler.h"

#include "main.h"

#include "../../stateMachine/service_stateMachine.h"

#include "../state/on/service_lightHandlerOn.h"
#include "../state/off/service_lightHandlerOff.h"
#include "../state/blinkOn/service_lightHandlerBlinkOn.h"
#include "../state/blinkOff/service_lightHandlerBlinkOff.h"

// dynamic light data
service_lightHandler_Light* service_lightHandler_currentlyHandledLight;

// state machine declaration
service_stateMachine_State service_lightHandler_states[SERVICE_LIGHTHANDLER_AMOUNT_OF_STATES];
service_stateMachine_StateMachine service_lightHandler_stateMachine;

void service_lightHandler_update(service_lightHandler_Light* light) {
    // set the usable pointer so we can update lights with the state machine
    service_lightHandler_currentlyHandledLight = light;
    // I think this is incredibly wrong, but I didn't find a better way to do this yet.
    // basically, we set a pointer that's going to be used as the variable to
    // provide data to all the states of the machhine during operation.
    
    // update time variable
    light->amountOfTimeThatLightDidntBlink += TEMPS_ECOULE_EN_MS_ENTRE_CHAQUE_INTERRUPTION;
    // yes, we're updating it even if we're not in blinking mode.
    // at first glance, it might seem like a bad operation to do, but it's actualy harmless.
    // When we switch back to the blinking mode, it's either going to be
    // reseted straight away (because its value is gonna be way too big),
    // or it's going to start at a random valid value within the blinking threshold time,
    // and start back from there to count the remainning cycles before the light blinks
    // and this variable gets reseted.
    //
    // Whatnot, its name is "amount of time that light didn't blink", and one can assume that it's not considered to
    // be blinking when it's either in the ON or OFF state.
    // Therefore, updating it when we're not in the "blinking" mode can still
    // be considered the correct thing to do, even if it's useless to do so! 
    
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