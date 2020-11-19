// serviceUsineCAN.h

// creator: Samuel Duclos
// date: 2020-11-16

#ifndef SERVICE_CAN_H
#define SERVICE_CAN_H

#define SERVICE_CAN_TRAME_BYTELENGTH 2;

void service_can_receiving_update();
void service_can_transmitting_update();

service_can_LabeledData dataReceivedFromCanForPosteDeCommande;
service_can_LabeledData dataToSendFromCanForCentreDeTri;
service_can_LabeledData dataReceivedFromCanForCentreDesTransports;
service_can_LabeledData dataReceivedFromCanForCentreDePesage;

typedef enum {
    OFF,
    ON,
    WAIT,
    TEST,
    ERROR0,
    ERROR1,
    ERROR2,
    ERROR3
} service_can_FunctionningMode; 

typedef enum {
    NOTHING,
    BLACK,
    ORANGE,
    METAL
} service_can_BlocColor;

typedef enum {
    A,
    B,
    C,
    D
} service_can_CarPosition; 

typedef enum {
    GRAMS,
    OZ
} service_can_MassUnit;

typedef struct {
    unsigned int mode : 3,
    color : 2,
    position : 2,
    unit : 1,
    weight : 8;
} service_can_Trame;

typedef struct {
    service_can_Trame data;
    unsigned char senderId;
} service_can_LabeledData;

#endif
 