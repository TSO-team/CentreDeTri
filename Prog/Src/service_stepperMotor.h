// service_stepperMotor.h

#ifndef SERVICE_STEPPERMOTOR_H
#define SERVICE_STEPPERMOTOR_H

typedef struct {
    long position;
    long destination;
    int velocity;
    float amountOfTimeThatStepperDidntMove;
    void(*driveStepper)(unsigned char byteValue);
} service_stepperMotor_Stepper;

void service_stepperMotor_init(service_stepperMotor_Stepper* stepper);
void service_stepperMotor_update(service_stepperMotor_Stepper* stepper);

#endif
