// serviceUsineCAN.c
// 
// date: 2020-11-19, John-William Lebel, creation
// date: 2020-11-21, John-William Lebel, changed the names of some elements for clarity

#include "service_can.h"
#include "main.h"
#include "piloteCAN1.h"

float elapsedTimeInMsFromMasterSync;
unsigned char isDataSent;

service_can_LabeledData service_can_dataReceivedPosteDeCommande =     {0, 0, 0, 0, 0, 0};
service_can_LabeledData service_can_dataToSendCentreDeTri =           {0, 0, 0, 0, 0, 0};
service_can_LabeledData service_can_dataReceivedCentreDesTransports = {0, 0, 0, 0, 0, 0};
service_can_LabeledData service_can_dataReceivedCentreDePesage =      {0, 0, 0, 0, 0, 0};

void service_can_read(service_can_LabeledData* labeledData);
void service_can_write(service_can_Trame* dataToSend);
void transferLabeledData(service_can_LabeledData* from, service_can_LabeledData* into);

void service_can_init() {
    elapsedTimeInMsFromMasterSync = 0;
    isDataSent = 1;
}

void service_can_receivingUpdate() {
    // get can data in a temp variable (I know this is ugly, but it should work).
    // make sure to set the senderId variable to an invalide id beforehand so
    // we can know if we received anything or not
    service_can_LabeledData tempLabeledData = {0, 0, 0, 0, 0, SERVICE_CAN_NO_RECEPTION_ID};
    service_can_read(&tempLabeledData);
    
    // we enter this if section if we are less than 80ms from
    // the "poste de commande" sync time
    if(elapsedTimeInMsFromMasterSync < 80) {
        // update the time counter
        elapsedTimeInMsFromMasterSync += TEMPS_ECOULE_EN_MS_ENTRE_CHAQUE_INTERRUPTION;
        
        // save 2 ifs!
        // this is worth doing because a lot of times when we're ready to gather
        // can data, no station sent anything yet. Ah, saving precious cycles...
        if(tempLabeledData.senderId == SERVICE_CAN_NO_RECEPTION_ID) {
            return;
        }
        // centre des transports sent?
        else if(tempLabeledData.senderId == SERVICE_CAN_CENTRE_DES_TRANSPORT_ID) {
            // map the data
            transferLabeledData(&tempLabeledData,
                                &service_can_dataReceivedCentreDesTransports);
        }
        // centre de pesage sent?
        else if(tempLabeledData.senderId == SERVICE_CAN_CENTRE_DE_PESAGE_ID) {
            // map the data
            transferLabeledData(&tempLabeledData,
                                &service_can_dataReceivedCentreDePesage);
        }
    }
    // sync with "poste de commande"
    else {
        // wait for "poste de commande" to send data so we can sync
        if(tempLabeledData.senderId == SERVICE_CAN_POSTE_DE_COMMANDE_ID) {
            transferLabeledData(&tempLabeledData,
                                &service_can_dataReceivedPosteDeCommande);
          
            // reset the counter
            elapsedTimeInMsFromMasterSync = 0;
            
            // enable back sending on can port
            isDataSent = 0;
        }
    }
}

void service_can_transmittingUpdate() {
    if(elapsedTimeInMsFromMasterSync < 20) {
        return;
    }
    if(isDataSent) {
        return;
    }
    service_can_write(&service_can_dataToSendCentreDeTri.data);
    isDataSent = 1;
}

void service_can_read(service_can_LabeledData* labeledData) {
    if(piloteCAN1_messageDisponible()) {
        piloteCAN1_litUnMessageRecu((unsigned char*)&(labeledData->data), &(labeledData->senderId));
    }
}

void service_can_write(service_can_Trame* dataToSend) {
    piloteCAN1_transmetDesDonnes(PILOTECAN1_MASQUE_11_BITS_EN_RECEPTION,
                                 (unsigned char*)dataToSend,
                                 SERVICE_CAN_TRAME_BYTELENGTH);
}

void transferLabeledData(service_can_LabeledData* from, service_can_LabeledData* into) {
    into->data.mode =     from->data.mode;
    into->data.color =    from->data.color;
    into->data.position = from->data.position;
    into->data.unit =     from->data.unit;
    into->data.weight =   from->data.weight;
    
    into->senderId =      from->senderId;
}

 