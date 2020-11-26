//driver_testButton.h

#ifndef DRIVER_TESTBUTTON_H
#define DRIVER_TESTBUTTON_H

//MODULE: driver_testButton
//DESCRIPTION: pour lire l'entree IOB1
//HISTORIQUE:
// 2018-09-08, Yves Roy, creation
// 2020-11-21, John-William Lebel, updated pin and port names, changed filename slightly to match project doc

//DEFINITIONS REQUISES PAR LE MODULE:
//Dependances materielles
//(copiez et adaptez ce qui suit dans "main.h")
//#define PILOTEIOB1_PORT B1_GPIO_Port
//#define PILOTEIOB1_ENTREE B1_Pin

//Dependances logicielles
//(copiez et adaptez ce qui suit dans "main.h")
//pas de dépendances logicielles

//INFORMATION PUBLIQUE:
//Definitions publiques:
//pas de definitions publiques

//Fonctions publiques:
void driver_testButton_init(void);
unsigned char driver_testButton_read(void);

//Variables publiques:
//pas de variables publiques

#endif
