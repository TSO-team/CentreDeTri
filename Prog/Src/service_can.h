// serviceUsineCAN.h

// creator: Samuel Duclos
// date: 2020-11-16
// modifications: 2020-11-19, John-William Lebel, ajout de l'addresse de l'envoyeur en can dans une nested structure

#ifndef SERVICE_CAN_H
#define SERVICE_CAN_H

void service_can_receivingUpdate();
void service_can_transmittingUpdate();

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
    unsigned int mode: 3,
    color: 2,
    position: 2,
    unit: 1,
    weight: 8;
} service_can_Trame;

typedef struct {
    service_can_Trame data;
    unsigned char senderId;
} service_can_LabeledData;

extern service_can_LabeledData dataReceivedFromCanForPosteDeCommande;
extern service_can_LabeledData dataToSendFromCanForCentreDeTri;
extern service_can_LabeledData dataReceivedFromCanForCentreDesTransports;
extern service_can_LabeledData dataReceivedFromCanForCentreDePesage;

#endif
 