//interfaceB1:
//Historique: 
// 2018-09-24, Yves Roy, creation
// 2020-10-22, John-William Lebel, complete redesing

//INCLUSIONS
#include "service_buttonUtils.h"
#include "main.h"

// defines
#define BUTTON_INTEGRAL_VALUE_BEFORE_CONSIDERED_PRESSED (unsigned char)(10/TEMPS_ECOULE_EN_MS_ENTRE_CHAQUE_INTERRUPTION)

// function prototypes
unsigned char unbounceButton(service_buttonUtils_Button* button, unsigned char rawButtonValue);
void updateButtonIntegral(service_buttonUtils_Button* button, unsigned char rawButtonValue);
void clampButtonIntegral(service_buttonUtils_Button* button);

// contructor (sort of?)
void service_buttonUtils_init(service_buttonUtils_Button* button) {
  button->unbouncedButtonValue = 0;
  button->previousUnbouncedButtonValue = 0;
  button->buttonIntegral = 0;
}

// this is called to avoid multiple updates of the integral value
// when calling more than one function that wants to know the state of 
// the unbounced button
void service_buttonUtils_updateInternalValues(service_buttonUtils_Button* button, unsigned char buttonValue) {
  button->previousUnbouncedButtonValue = button->unbouncedButtonValue;
  button->unbouncedButtonValue = unbounceButton(button, buttonValue);
}

// get the unbounced button state
unsigned char service_buttonUtils_pressed(service_buttonUtils_Button* button) {
  return button->unbouncedButtonValue;
}

// returns 1 if the button is on a rising edge
// returns 0 otherwise
unsigned char service_buttonUtils_clicked(service_buttonUtils_Button* button) {
  unsigned char hasClicked = 0;
  
  // rising edge?
  if(!button->previousUnbouncedButtonValue
     && button->unbouncedButtonValue) {
    hasClicked = 1;
  }
  
  return hasClicked;
}

// unbounce the button, and update private vars accordingly
unsigned char unbounceButton(service_buttonUtils_Button* button, unsigned char rawButtonValue) {
  unsigned char buttonValue = 0;
  
  updateButtonIntegral(button, rawButtonValue);
  clampButtonIntegral(button);
  if(button->buttonIntegral == BUTTON_INTEGRAL_VALUE_BEFORE_CONSIDERED_PRESSED) {
    buttonValue = 1;
  }
  
  return buttonValue;
}

// "integral" is just a fancy term for "addition".
// basically, add 1s to the counter until we hit the threshold value
void updateButtonIntegral(service_buttonUtils_Button* button, unsigned char rawButtonValue) {
  if(rawButtonValue) {
    button->buttonIntegral++;
  }
  else {
    button->buttonIntegral = 0;
  }
}

// make sure the integral doesn't overflow
void clampButtonIntegral(service_buttonUtils_Button* button) {
  if(button->buttonIntegral > BUTTON_INTEGRAL_VALUE_BEFORE_CONSIDERED_PRESSED) {
    button->buttonIntegral = BUTTON_INTEGRAL_VALUE_BEFORE_CONSIDERED_PRESSED;
  }
}