/**************************************************************************************************
Nom du fichier : Main.c
   Auteur : St�phane Desch�nes                  
   Date de cr�ation : 31 octobre 2020
	Version 0.1
	 Programme fourni avec le laboratoire sur le triac dans le cours 247-647
         
         1- Ce programme utilise le timer0 comme base de temps avec les flags uTimingFlags.

         2 - Ce programme utilise aussi le timer1.  Une interruption � tous les 100 us sont fait 
             lors du d�passement du timer 1. Il est configur� en autoreload (valeur 163 pour faire 100 us)
             Ce timer sera utile pour donner une latitude pour le contr�le du triac
        
         3 - Le zero crossing se lit sur P1, bit 6
             Le contr�le du triac se fait avec le P1, bit 7

            
    

***************************************************************************************************/

// *************************************************************************************************
//  INCLUDES
// *************************************************************************************************	
#include <ioDS89C450.h>         // D�finition des bits et des registres du microcontr�leur pour IAR

#include "main.h"               // 
#include "Interruption.h"

// *************************************************************************************************
//  CONSTANTES
// *************************************************************************************************

#define TRIAC_CTRL  P1_bit.P16_INT4
#define TRIAC_ZC    P1_bit.P17_INT5

// *************************************************************************************************
//  FONCTIONS LOCALES
// *************************************************************************************************

/* VIDE */

// *************************************************************************************************
//  STRUCTURES ET UNIONS
// *************************************************************************************************

/* VIDE */

// *************************************************************************************************
// VARIABLES LOCALES
// *************************************************************************************************

/*  VIDE */

// *************************************************************************************************
void main (void)
//
//  Auteur: St�phane Desch�nes 	
//  Date de cr�ation :  xx-xx-xx  - Date non utilis� pour le main
//  Version x.x  - Version non utilis� pour le main
//
//  Description: Appel� lorsque le programme d�marre
//  Param�tres d'entr�es : Aucun
//  Param�tres de sortie : Aucun
//  Notes     		 : Aucune
//
// *************************************************************************************************
{ 
  // D�sactiver les interruptions
  IE_bit.EA = 0;						
  // Initialise le timer 0 pour la base de temps g�n�rale
  vInitTimer0();
  vInitInterruptOverflowT0();
  
  // Initialise le timer 1 pour la base de temps qui servira pour contr�ler le triac
  vInitTimer1();
  vInitInterruptOverflowT1();
  
  // Activ� les interruptions
  IE_bit.EA = 1;																					 
  																	 
 	
  //Programme principal.	    
  while (1) 
  { 
    if(uTimingFlags.Bits.mSec1 == true)
    {      
      uTimingFlags.Bits.mSec1 = false;
      /* CHOSES � FAIRE AUX 1 MS  */
    }
    if(uTimingFlags.Bits.mSec10 == true)
    {
      uTimingFlags.Bits.mSec10 = false;
      /* CHOSES � FAIRE AUX 10 MS */
    }
    if(uTimingFlags.Bits.mSec100 == true)
    {      
      uTimingFlags.Bits.mSec100 = false;
      /* CHOSES � FAIRE AUX 100 MS */
    }
  }
}


