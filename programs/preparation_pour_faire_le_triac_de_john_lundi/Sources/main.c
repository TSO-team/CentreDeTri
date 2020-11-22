/**************************************************************************************************
Nom du fichier : Main.c
   Auteur : Stéphane Deschênes                  
   Date de création : 31 octobre 2020
	Version 0.1
	 Programme fourni avec le laboratoire sur le triac dans le cours 247-647
         
         1- Ce programme utilise le timer0 comme base de temps avec les flags uTimingFlags.

         2 - Ce programme utilise aussi le timer1.  Une interruption à tous les 100 us sont fait 
             lors du dépassement du timer 1. Il est configuré en autoreload (valeur 163 pour faire 100 us)
             Ce timer sera utile pour donner une latitude pour le contrôle du triac
        
         3 - Le zero crossing se lit sur P1, bit 6
             Le contrôle du triac se fait avec le P1, bit 7

            
    

***************************************************************************************************/

// *************************************************************************************************
//  INCLUDES
// *************************************************************************************************	
#include <ioDS89C450.h>         // Définition des bits et des registres du microcontrôleur pour IAR

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
//  Auteur: Stéphane Deschênes 	
//  Date de création :  xx-xx-xx  - Date non utilisé pour le main
//  Version x.x  - Version non utilisé pour le main
//
//  Description: Appelé lorsque le programme démarre
//  Paramètres d'entrées : Aucun
//  Paramètres de sortie : Aucun
//  Notes     		 : Aucune
//
// *************************************************************************************************
{ 
  // Désactiver les interruptions
  IE_bit.EA = 0;						
  // Initialise le timer 0 pour la base de temps générale
  vInitTimer0();
  vInitInterruptOverflowT0();
  
  // Initialise le timer 1 pour la base de temps qui servira pour contrôler le triac
  vInitTimer1();
  vInitInterruptOverflowT1();
  
  // Activé les interruptions
  IE_bit.EA = 1;																					 
  																	 
 	
  //Programme principal.	    
  while (1) 
  { 
    if(uTimingFlags.Bits.mSec1 == true)
    {      
      uTimingFlags.Bits.mSec1 = false;
      /* CHOSES À FAIRE AUX 1 MS  */
    }
    if(uTimingFlags.Bits.mSec10 == true)
    {
      uTimingFlags.Bits.mSec10 = false;
      /* CHOSES À FAIRE AUX 10 MS */
    }
    if(uTimingFlags.Bits.mSec100 == true)
    {      
      uTimingFlags.Bits.mSec100 = false;
      /* CHOSES À FAIRE AUX 100 MS */
    }
  }
}


