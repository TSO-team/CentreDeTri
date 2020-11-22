// service_triac.h

#ifndef SERVICE_TRIAC_H
#define SERVICE_TRIAC_H

#define SERVICE_TRIAC_120V_FREQUENCY 60
// we're passing by zero 2 times per oscillation
#define SERVICE_TRIAC_EXPECTED_REFRESH_RATE (SERVICE_TRIAC_120V_FREQUENCY * 2)
#define SERVICE_TRIAC_EXPECTED_MAX_PULSE_DURATION_IN_MS (1000.0 / SERVICE_TRIAC_EXPECTED_REFRESH_RATE)

typedef struct {
    float dutyCycle;
    float timeFromPassageByZero;
    void (*driveTriac)(unsigned char outputValue);
    unsigned char (*isPassingByZero)(void);
} service_triac_Triac;

void service_triac_init(service_triac_Triac* triac);
void service_triac_update(service_triac_Triac* triac);

#endif
