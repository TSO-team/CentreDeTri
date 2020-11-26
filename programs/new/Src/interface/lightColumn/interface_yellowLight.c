// interface_yellowLight.c
// 
// creator: John-William Lebel
// date: 2020-10-08

#include "interface_yellowLight.h"
#include "main.h"
#include "../../driver/lightColumn/driver_yellowLight.h"

void interface_yellowLight_init() {
}

void interface_yellowLight_writeOutputByte(unsigned char outputBit) {
    driver_yellowLight_set(outputBit);
}

