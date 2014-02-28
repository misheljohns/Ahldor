#ifndef Multiplexer_h //because we include multiplexer in LineFind, and if this isn't there, there will be a multiple definition error
#define Multiplexer_h

/*---------------- Includes ---------------------------------*/

#if defined(ARDUINO) && ARDUINO >= 100 
#include "Arduino.h"  // if Arduino version 1.0 or later, include Arduino.h
#else
#include "WProgram.h"  // if Arduino version 22, include WProgram.h
#endif

#include "Defines.h"

/*---------------- Module Variables -------------------------*/
/*
byte controlPins[] = {
                  B00000000, //0 
                  B00001000, //1
                  B00000100, //2
                  B00001100,
                  B00000001,
                  B00001001,
                  B00000101,
                  B00001101,
                  B00000010,
                  B00001010,
                  B00000110,
                  B00001110,
                  B00000011,
                  B00001011,
                  B00000111,
                  B00001111 }; //15
*/
/*---------------- Module Functions -------------------------*/


void InitMux()
{
  //pinmodes for A0 to A3 - OUT
  pinMode(A0, OUTPUT);
  pinMode(A1, OUTPUT);
  pinMode(A2, OUTPUT);
  pinMode(A3, OUTPUT);
  
  //A4 - IN without pullup
  pinMode(A4, INPUT);
}

void SelectIn(byte inp)
{
  //PORTC = controlPins[inp];
  PORTC = inp;//faster to change wiring
  __asm__ __volatile__ ("nop\n\t"); //wait one cycle (62.5ns) for input to settle before reading
}

byte ReadIn()
{
  return bitRead(PINC, 4);
}

#endif //because we include multiplexer in LineFind, and if this isn't there, there will be a multiple definition error
