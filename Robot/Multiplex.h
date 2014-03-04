/****************************************************
 * Multiplexing
 * Prefix: MUX
 ****************************************************/
 
#ifndef MUX_H
#define MUX_H

/*---------------- Includes ---------------------------------*/

#include "Arduino.h"
#include "Defines.h"

/*---------------- Module Constants -------------------------*/

#define MUX_PRINT_RATE 50

/*---------------- Module Variables -------------------------*/

//static Timer* timer_mux;

int mux_print_pin;
int event_mux_print;

/*---------------- Module Functions -------------------------*/

void MUX_select_in(byte inp)
{
  //PORTC = controlPins[inp];
  PORTC = PORTC & B11110000;
  PORTC = PORTC | inp;
  
  //wait one cycle (62.5ns) for input to settle before reading
  __asm__ __volatile__ ("nop\n\t"); 
}

int MUX_read(byte mux_pin) {
  MUX_select_in(mux_pin);
  return analogRead(MUX_IN);
}

void MUX_print_raw() {
  Serial.println("MUX pin " + String(mux_pin) + " has value " + String(MUX_read(mux_print_pin)));
}

void MUX_print(int mux_pin) {
  mux_print_pin = mux_pin;
  MUX_print_raw();
}

void MUX_print_start(int mux_pin) {
  mux_print_pin = mux_pin;
  event_mux_print = t->every(MUX_PRINT_RATE, MUX_print_raw);
}

void MUX_print_stop() {
  t->stop(event_mux_print);
}

void print_0() {
  Serial.println("4: " + String(MUX_read(4)) + " 5: " + String(MUX_read(5)) + " 6: " + String(MUX_read(6)));
}

void MUX_Init(Timer* t) {
  
  //pinmodes for A0 to A3 - OUT
  pinMode(MUX_S0, OUTPUT);
  pinMode(MUX_S1, OUTPUT);
  pinMode(MUX_S2, OUTPUT);
  pinMode(MUX_S3, OUTPUT);
  
  //A4 - IN without pullup
  pinMode(MUX_IN, INPUT);
  
  timer = t;
  //timer->every(50, print_0);
  
  Serial.println("MUX module initialized!");
}

void MUX_commands() {
  COMM_check_command(String("MUX"), MUX_print);
  COMM_check_command(String("MUX_START"), MUX_print_start);
  COMM_check_command(String("MUX_STOP"), MUX_print_stop);
}

#endif /* MUX_H */
