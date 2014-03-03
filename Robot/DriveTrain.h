/****************************************************
 * Drivetrain
 * Prefix: Drive
 ****************************************************/
 
#ifndef DRIVE_H
#define DRIVE_H

/*---------------- Includes ---------------------------------*/

#include "Arduino.h"
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
  
void DRIVE_Init() {
  
}

#endif /* DRIVE_H */

