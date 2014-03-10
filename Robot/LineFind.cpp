/****************************************************
 * Line Sensing (Tape)
 * Prefix: LINE
 ****************************************************/

/*---------------- Includes ---------------------------------*/

#include "LineFind.h"


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
  return (MUX_read_digital(MUX_WALL_SWITCH_LEFT) && MUX_read_digital(MUX_WALL_SWITCH_RIGHT));
}

void LINE_PrintAtServer() {
  Serial.println("At Server! :"+String(LINE_AtServer()));
}

void LINE_commands() {
  COMM_check_command(String("AT_SERVER"), LINE_PrintAtServer); 
}

