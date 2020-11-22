// interface_greenLight.c
// 
// creator: John-William Lebel
// date: 2020-10-08

#include "interface_greenLight.h"
#include "main.h"
#include "../../driver/lightColumn/driver_greenLight.h"

void interface_greenLight_init() {
}

void interface_greenLight_writeOutputByte(unsigned char outputBit) {
    driver_greenLight_set(outputBit);
}

