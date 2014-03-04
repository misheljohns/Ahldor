/****************************************************
 * Line Sensing (Tape)
 * Prefix: LINE
 ****************************************************/
 
#ifndef LINE_H
#define LINE_H

/*---------------- Includes ---------------------------------*/

#include "Arduino.h"
#include "Defines.h"
#include "Multiplex.h"

/*---------------- Module Defines ---------------------------*/

#define LINESENSOR_THRESHOLD 10

/*---------------- Module Functions -------------------------*/

byte RearSensor()
{
  int rear_value = MUX_read(MUX_FRONT_LINESENSOR);
  if(rear_value < LINESENSOR_THRESHOLD)
  {
    return 1;
  }
  else
  {
    return 0;
  }
}

byte LeftSensor()
{
  int frontl_value = MUX_read(MUX_BACKL_LINESENSOR);
  if(frontl_value < LINESENSOR_THRESHOLD)
  {
    return 1;
  }
  else
  {
    return 0;
  }
}

byte RightSensor()
{
  int frontr_value = MUX_read(MUX_BACKR_LINESENSOR);
  if(frontr_value < LINESENSOR_THRESHOLD)
  {
    return 1;
  }
  else
  {
    return 0;
  }
}

void LINE_Init(Timer* t) {
  Serial.println("LINE module initialized!");
}

void LINE_commands() {
  
}

#endif /* LINE_H */
