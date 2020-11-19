// serviceUsineCAN.c

// creator: John-William Lebel
// date: 2020-11-19

#include "service_can.h"
#include "main.h"
#include "piloteCAN1.h"

float elapsedTimeInMsFromMasterSync;
unsigned char isDataSent;

extern service_can_LabeledData dataReceivedFromCanForPosteDeCommande;
extern service_can_LabeledData dataToSendFromCanForCentreDeTri;
extern service_can_LabeledData dataReceivedFromCanForCentreDesTransports;
extern service_can_LabeledData dataReceivedFromCanForCentreDePesage;

void service_can_init() {
    elapsedTimeInMsFromMasterSync = 0;
    isDataSent = 1;
    
    dataReceivedFromCanForPosteDeCommande = {0, 0};
    dataReceivedFromCanForCentreDesTransports = {0, 0};
    dataReceivedFromCanForCentreDePesage = {0, 0};
}

void service_can_receiving_update() {
    if(elapsedTimeInMsFromMasterSync < 80) {
        elapsedTimeInMsFromMasterSync += TEMPS_ECOULE_EN_MS_ENTRE_CHAQUE_INTERRUPTION;
        
        if(elapsedTimeInMsFromMasterSync >= 60) {
            service_can_read(&dataReceivedFromCanForCentreDePesage);
        }
        else if(elapsedTimeInMsFromMasterSync >= 40) {
            service_can_read(&dataReceivedFromCanForCentreDesTransports);
        }
    }
    else {
        service_can_read(&dataReceivedFromCanForPosteDeCommande);
        if(dataReceivedFromCanForCentreDesTransports.senderId == SERVICE_CAN_POSTE_DE_COMMANDE_ID) {
            elapsedTimeInMsFromMasterSync = 0;
            isDataSent = 0;
        }
    }
}

void service_can_transmitting_update() {
    if(elapsedTimeInMsFromMasterSync >= 20) {
        if(!isDataSent) {
            service_can_write(&dataToSendFromCanForCentreDeTri.data);
            isDataSent = 1;
        }
    }
}

void service_can_read(service_can_LabeledData* labeledData) {
    if(piloteCAN1_messageDisponible()) {
        piloteCAN1_litUnMessageRecu(&(*labeledData).data, &(*labeledData).senderId);
    }
}

void service_can_write(service_can_Trame* dataToSend) {
    piloteCAN1_transmetDesDonnes(PILOTECAN1_MASQUE_11_BITS_EN_RECEPTION,
                                 dataToSend,
                                 SERVICE_CAN_TRAME_BYTELENGTH);
}

 