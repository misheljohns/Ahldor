/****************************************************
 * Multiplexing
 * Prefix: MUX
 ****************************************************/
 
#ifndef MUX_H
#define MUX_H

/*---------------- Includes ---------------------------------*/

#include "Arduino.h"
#include "Timer.h"
#include "Communication.h"
#include "Defines.h"

/*---------------- Module Constants -------------------------*/

#define MUX_PRINT_RATE 50

/*---------------- Module Functions -------------------------*/

void MUX_select_in(byte inp);
int MUX_read(byte mux_pin) ;
int MUX_read_digital(byte mux_pin);
void MUX_print_raw();
void MUX_print_raw_digital();
void MUX_print(int mux_pin);
void MUX_print_stop();
void MUX_print_start(int mux_pin);
void MUX_print_line();
void MUX_Init(Timer* t);
void MUX_commands();

#endif /* MUX_H */
