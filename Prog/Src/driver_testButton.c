//driver_testButton.c:
//Historique: 
// 2018-09-08, Yves Roy, creation

//INCLUSIONS
#include "main.h"
#include "driver_testButton.h"

//Definitions privees
//pas de définitions privees

//Declarations de fonctions privees:
//pas de fonction privees

//Definitions de variables privees:
//pas de variables privees

//Definitions de fonctions privees:
//pas de fonctions privees

//Definitions de variables publiques:
// pas de variables publiques

//Definitions de fonctions publiques:
void driver_testButton_init(void) {
  //on pose que le cube a fait la configuration par defaut
}

unsigned char driver_testButton_read(void) {
  return HAL_GPIO_ReadPin(testButton_GPIO_Port, testButton_Pin);
}




