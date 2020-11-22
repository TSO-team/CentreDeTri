// interface_redLight.c
// 
// creator: John-William Lebel
// date: 2020-10-08

#include "interface_redLight.h"
#include "main.h"
#include "driver_redLight.h"

void interface_redLight_init() {
}

void interface_redLight_writeOutputByte(unsigned char outputBit) {
    driver_redLight_set(outputBit);
}

