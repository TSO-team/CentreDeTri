#ifndef INTERFACEB1_H
#define INTERFACEB1_H

//HISTORIQUE:
// 2018-09-08, Yves Roy, creation
// 2020-10-22, John-William Lebel, complete redesing
// 2020-11-20, John-William Lebel, added ability to handle multiple buttons at the same time

typedef struct {
    unsigned char unbouncedButtonValue;
    unsigned char previousUnbouncedButtonValue;
    signed int buttonIntegral;
} service_buttonUtils_Button;

void service_buttonUtils_init(service_buttonUtils_Button* button);
void service_buttonUtils_updateInternalValues(service_buttonUtils_Button* button, unsigned char buttonValue);
unsigned char service_buttonUtils_pressed(service_buttonUtils_Button* button);
unsigned char service_buttonUtils_clicked(service_buttonUtils_Button* button);

#endif
