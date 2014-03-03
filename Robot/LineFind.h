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
  SelectIn(REAR_LINESENSOR);
  if(ReadIn() < LINESENSOR_THRESHOLD)
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
  SelectIn(FRONTL_LINESENSOR);
  if(ReadIn() < LINESENSOR_THRESHOLD)
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
  SelectIn(FRONTR_LINESENSOR);
  if(ReadIn() < LINESENSOR_THRESHOLD)
  {
    return 1;
  }
  else
  {
    return 0;
  }
}

void LINE_Init() {
  
}

#endif /* LINE_H */
