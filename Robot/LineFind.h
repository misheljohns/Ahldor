/****************************************************
 * Line Sensing (Tape)
 * Prefix: LINE
 ****************************************************/
 
#ifndef LINE_H
#define LINE_H

/*---------------- Includes ---------------------------------*/

#include "Arduino.h"
#include "Timer.h"
#include "Communication.h"
#include "Defines.h"
#include "Multiplex.h"

/*---------------- Module Defines ---------------------------*/

#define LINESENSOR_THRESHOLD 110

/*---------------- Module Functions -------------------------*/

byte LINE_front();
byte LINE_back_left();
byte LINE_back_right();
void LINE_Init(Timer* t);
byte LINE_AtServer();
void LINE_PrintAtServer();
void LINE_commands() ;

#endif /* LINE_H */
