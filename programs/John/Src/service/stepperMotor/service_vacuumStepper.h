// service_vacuumStepper.h

#ifndef SERVICE_VACUUMSTEPPER_H
#define SERVICE_VACUUMSTEPPER_H

typedef enum {
    A,
    B,
    C,
    D,
    E,
    //...? How many!
} service_vacuumStepper_Position;

typedef struct {
    service_vacuumStepper_Position position;
} service_vacuumStepper_Stepper;

void service_vacuumStepper_init();
void service_vacuumStepper_update(service_vacuumStepper_Stepper* stepper);

#endif
