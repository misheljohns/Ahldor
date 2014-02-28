/*---------------- Includes ---------------------------------*/

#if defined(ARDUINO) && ARDUINO >= 100 
#include "Arduino.h"  // if Arduino version 1.0 or later, include Arduino.h
#else
#include "WProgram.h"  // if Arduino version 22, include WProgram.h
#endif

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

