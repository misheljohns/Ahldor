/*---------------- Includes ---------------------------------*/

#if defined(ARDUINO) && ARDUINO >= 100 
#include "Arduino.h"  // if Arduino version 1.0 or later, include Arduino.h
#else
#include "WProgram.h"  // if Arduino version 22, include WProgram.h
#endif

#include "Defines.h"

/*---------------- Module Functions -------------------------*/

void InitMotors()
{
  //brakes off
  PORTB = PORTB & B11111100;//PB0 and PB1 set to LOW
}

void BrakeMotors()
{
  PORTB = PORTB | B00000011;//PB0 and PB1 set to HIGH
}
  


