/****************************************************
 * Multiplexing
 * Prefix: MUX
 ****************************************************/
 
#ifndef MUX_H
#define MUX_H

/*---------------- Includes ---------------------------------*/

#include "Arduino.h"
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

void MUX_Init() {
  
  //pinmodes for A0 to A3 - OUT
  pinMode(A0, OUTPUT);
  pinMode(A1, OUTPUT);
  pinMode(A2, OUTPUT);
  pinMode(A3, OUTPUT);
  
  //A4 - IN without pullup
  pinMode(A4, INPUT);
  
  Serial.println("MUX module initialized!");
}

#endif /* MUX_H */
