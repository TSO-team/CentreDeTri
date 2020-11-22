// service_stepperMotor:
// Historique: 
// 2020-10-22, John-William Lebel, creation

#include "service_stepperMotor.h"
#include "main.h"

const unsigned char stepperPositions[] = {5, 6, 10, 9};

void advanceOneStep(service_stepperMotor_Stepper* stepper);

// initialization
void service_stepperMotor_init(service_stepperMotor_Stepper* stepper) {
    unsigned char stepperStartingPositionIndex = stepper->position & 3;
    stepper->driveOutput(stepperPositions[stepperStartingPositionIndex]);
}

// step the motor if the function has been called enough
void service_stepperMotor_update(service_stepperMotor_Stepper* stepper) {
    stepper->amountOfTimeThatStepperDidntMove += TEMPS_ECOULE_EN_MS_ENTRE_CHAQUE_INTERRUPTION;
    
    if(stepper->amountOfTimeThatStepperDidntMove > (1000.0/stepper->velocity)) {
        stepper->amountOfTimeThatStepperDidntMove = 0;
        advanceOneStep(stepper);
    }
}

// step for real
void advanceOneStep(service_stepperMotor_Stepper* stepper) {
    if(stepper->destination - stepper->position > 0) {
        stepper->position++;
    }
    else if(stepper->destination - stepper->position < 0) {
        stepper->position--;
    }
    unsigned char stepperPositionIndex = stepper->position & 3;
    stepper->driveOutput(stepperPositions[stepperPositionIndex]);
}