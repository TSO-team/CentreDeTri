// interface_pcf8574A.h
// 
// interface for the mcp23008 general io expander
// this specific driver defines functions to put the chip's IOs into readonly inputs.
// creator: John-William Lebel
// date: 2020-10-08

#ifndef INTERFACE_YELLOWLIGHT_H
#define INTERFACE_YELLOWLIGHT_H

/* put this in main.h if you're using it and it's not there
#define PCF8574A_CHIP_ADDRESS 0x7A
*/

void interface_yellowLight_init();
void interface_yellowLight_writeOutputByte(unsigned char outputBit);

#endif