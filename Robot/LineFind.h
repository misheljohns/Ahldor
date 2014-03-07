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

#define LINESENSOR_THRESHOLD 110

/*---------------- Module Functions -------------------------*/

byte LINE_front()
{
  int front_value = MUX_read(MUX_FRONT_LINESENSOR);
  return (front_value < LINESENSOR_THRESHOLD);
}

byte LINE_back_left()
{
  int rearl_value = MUX_read(MUX_BACKL_LINESENSOR);
  return (rearl_value < LINESENSOR_THRESHOLD);
}

byte LINE_back_right()
{
  int backr_value = MUX_read(MUX_BACKR_LINESENSOR);
  return (backr_value < LINESENSOR_THRESHOLD);
}

void LINE_Init(Timer* t) {
  Serial.println("LINE module initialized!");
}

byte LINE_AtServer()
{
  return (MUX_read(MUX_WALL_SWITCH_LEFT) && MUX_read(MUX_WALL_SWITCH_RIGHT));
}

void LINE_commands() {
  
}

#endif /* LINE_H */
