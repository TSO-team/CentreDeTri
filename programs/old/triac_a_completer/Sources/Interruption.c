/**************************************************************************************************
   Nom du fichier : Interrupt.c
   Auteur : St�phane Desch�nes                  
   Date de cr�ation : 11 f�vrier 2019
  
    Description: Contient les fichiers pour l'initialisation du/des timer et fonctions d'interruption
         		
    Versions:
      1.0:  Premi�re version
								
***************************************************************************************************/


// *************************************************************************************************
//  INCLUDES
// *************************************************************************************************	
#include <ioDS89C450.h>         // D�finition des bits et des registres du microcontr�leur pour IAR
#include "Interruption.h"
#include "main.h"
// *************************************************************************************************
//  CONSTANTES
// *************************************************************************************************

/* VIDE */

// *************************************************************************************************
//  FONCTIONS LOCALES
// *************************************************************************************************

/* VIDE */

// *************************************************************************************************
//  STRUCTURES ET UNIONS
// *************************************************************************************************

/* VIDE */

/// ************************************************************************************************
// VARIABLES GLOBALES (D�clar� en extern dans .h)
// ************************************************************************************************
union UTimingFlags uTimingFlags;
unsigned char ucTriacDelay;
  
// *************************************************************************************************
// VARIABLES LOCALES
// *************************************************************************************************
/* VIDE */


/// *************************************************************************************************
void vInitTimer0(void)
//
//  Auteur: St�phane Desch�nes 	
//  Date de cr�ation :  11-02-19
//  Version 1.0
//
//  Description: Initialise le timer 0 pour qu'il fonctionne sur 16 bits.
//  Param�tres d'entr�es : Aucun
//  Param�tres de sortie : Aucun
//  Notes     		       : Aucune
//
// *************************************************************************************************
{
  TMOD = TMOD | 0x01;	        // 0x01 set the timer 0 as a 16-bit timer 
  TH0 = 0x00;		// Initialize the timer to 0                           
  TL0 = 0x00;
  TCON_bit.TR0 = 1;     // Srart timer 0
}

// *************************************************************************************************
void vInitInterruptOverflowT0(void)
//
//  Auteur: St�phane Desch�nes 	
//  Date de cr�ation :  11-02-19
//  Version 1.0
//
//  Description: Active l'interruption du timer 0
//  Param�tres d'entr�es : Aucun
//  Param�tres de sortie : Aucun
//  Notes     		       : Aucune
//
// *************************************************************************************************
{
  IE_bit.ET0 = 1;       // Enable timer 0 interruption  
}

/// *************************************************************************************************
void vInitTimer1(void)
//
//  Auteur: St�phane Desch�nes 	
//  Date de cr�ation :  11-02-19
//  Version 1.0
//
//  Description: Initialise le timer 1 pour qu'il fonctionne sur 8 bits avec autoreload
//  Param�tres d'entr�es : Aucun
//  Param�tres de sortie : Aucun
//  Notes     		       : Aucune
//
// *************************************************************************************************
{
  TMOD = TMOD | 0x20;   // 0x20 set the timer 1 as a 8-bit timer with autoreload 
  TH1 = 163;		// Initialize autoreload value to have interruption at each 100 us                     
  TL1 = 163;            //255 - (100 us * 11059200 / 12) =  163       
  TCON_bit.TR1 = 1;     // Srart timer 1
}

// *************************************************************************************************
void vInitInterruptOverflowT1(void)
//
//  Auteur: St�phane Desch�nes 	
//  Date de cr�ation :  11-02-19
//  Version 1.0
//
//  Description: Active l'interruption du timer 0
//  Param�tres d'entr�es : Aucun
//  Param�tres de sortie : Aucun
//  Notes     		       : Aucune
//
// *************************************************************************************************
{
  IE_bit.ET1 = 1;       // Enable timer 1 interruption  
}






#pragma vector = TF0_int
// *************************************************************************************************
__interrupt void T0_int (void)
//
//  Auteur: St�phane Desch�nes 	
//  Date de cr�ation :  19-01-07
//  Version 1.0
//      
//  Description: interruption du timer 0, arrive lorsque le timer passe de 0xFFFF � 0
//  Param�tres d'entr�es : Aucun
//  Param�tres de sortie : Aucun
//  Notes   	         : Le timer 0 est initialis� comme un timer de 16 bit. 
//                       en r�initialisant le timer � 56320, l'interruption arrive � tous les 10 ms.
//			   Calcul:  65536 - (1 ms * 11059200 / 12) =  64614
//                                      (65536 - 56320) * 12 / 11059200 = 1 ms
//
// *************************************************************************************************	
{
  #define VALUE_10_MS  10
  #define VALUE_100_MS  100
  static unsigned int uiCounter = 0;
      
  IE_bit.EA = 0;	// Disable the global interrupt
  TCON_bit.TR0 = 0;	// Disable timer 0
  TCON_bit.TF0 = 0;	// timer overflow flag
	
  TH0 = (64614 & 0xFF00) >>8;
  TL0 = 64614 & 0x00FF;
  
 
  uiCounter++;
  uTimingFlags.Bits.mSec1 = true;
   
  
  if (uiCounter % VALUE_10_MS  == 0)
  {
    uTimingFlags.Bits.mSec10 = true; 
  }
  if (uiCounter % VALUE_100_MS  == 0)
  {
    uTimingFlags.Bits.mSec100 = true;
    uiCounter = 0;   
  }  
  IE_bit.EA = 1; 
  TCON_bit.TR0 = 1;
}



#pragma vector = TF1_int
// *************************************************************************************************
__interrupt void T1_int (void)
//
//  Auteur: St�phane Desch�nes 	
//  Date de cr�ation :  19-01-07
//  Version 1.0
//      
//  Description: interruption du timer 1, arrive lorsque le timer passe de 0xFF � 0
//  Param�tres d'entr�es : Aucun
//  Param�tres de sortie : Aucun
//  Notes   	         : Le timer 1 est initialis� comme un timer de 8 bit autoreload (avec la valeur 163 
//
//                         255 - (100 us * 11059200 / 12) =  163 
//                         L'interruption aura donc lieu � tous les 100 us                           
// *************************************************************************************************	
{
  
  TCON_bit.TR1 = 0;	// Disable timer 1
  TCON_bit.TF1 = 0;	// timer overflow flag
 
  ucTriacDelay++; 
  TCON_bit.TR1 = 1;
}