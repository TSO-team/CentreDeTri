/****************************************************************************************
   Nom du fichier : Interruption.h
   Auteur : Stéphane Deschênes                  
  Date de création : 19-01-18
        Fichier de déclaration et de définition pour les fonctions d'initialisation de timer et 
        les fonctions d'interruptions
  
****************************************************************************************/
#ifndef INITERRUPTIONH
#define INITERRUPTIONH
// *************************************************************************************************
//  FONCTIONS GLOBALES
// *************************************************************************************************
void vInitTimer0(void);
void vInitInterruptOverflowT0(void);
void vInitTimer1(void);
void vInitInterruptOverflowT1(void);

// *************************************************************************************************
//  STRUCTURES ET UNIONS
// *************************************************************************************************
struct STimingFlags
{  
  char mSec1    :1;      // 1 mSec occured  
  char mSec10   :1; 	// 10 mSec occured
  char mSec100  :1;     // 100 mSec occured
  char Empty    :5;	// 5 bits still unused
};

union UTimingFlags
{
  char All;
  struct STimingFlags Bits;
};
// ************************************************************************************************
// VARIABLES GLOBALES
// ************************************************************************************************
extern union UTimingFlags uTimingFlags;
extern unsigned char ucTriacDelay;

#endif

