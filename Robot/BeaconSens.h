/****************************************************
 * Beacon Sensing
 * Prefix: BEACON
 ****************************************************/

#ifndef BEACON_H
#define BEACON_H

/*---------------- Includes ---------------------------------*/

#include "Arduino.h"
#include "Defines.h"

/*---------------- Module Functions -------------------------*/

unsigned long time;
volatile unsigned long time2;
volatile int count1;
double freq;
byte inLine;


int event_beacon_print;

void count()
{
  switch(count1++)
  {
    case 100:
      time2 = micros();
      break;
    case 0:
      time = micros();
      break;
  }
  inLine = 1;
}

byte IsInLine()
{
  byte tmp = inLine;
  inLine = 0;
  return tmp;
}

void InitFreqMeasure()
{
  pinMode(2, INPUT);
  attachInterrupt(0, count, RISING);
  count1 = 0;
}

double GetFreq()
{
  return freq;
}

byte BeaconDetected()
{
  if(time2 != 0)
  {
    freq = ((double)100000)/(double)(time2 - time);
    time2 = 0; 
    count1 = 0;
    return 1;
  }
  else return 0;
}

byte BeaconTypeDetected()
{
  if(time2 != 0)
  {
    freq = ((double)100000)/(double)(time2 - time);
    time2 = 0; 
    count1 = 0;
    if((freq > 2.9) && (freq < 3.1))
      return EXCHANGE_BEACON;
    else if((freq > 0.75) && (freq < 0.95))
      return SERVER_BEACON;
    else 
      return UNKNOWN_BEACON_FREQ;
    }
  else return 0;
}

void StopFreqMeasure()
{
  detachInterrupt(0);  
}

void BEACON_Init(Timer* t) {
  Serial.println("BEACON module initialized!");
}


void BEACON_print_raw() {
  Serial.print("BEACON TYPE ");
    Serial.print(BeaconTypeDetected());
  Serial.print(" has FREQ ");
  Serial.println(GetFreq());
}

void BEACON_print_start() {
  //MUX_print_stop();
  event_beacon_print = timer_mux->every(100, BEACON_print_raw);
}

void BEACON_print_stop() {
  timer_mux->stop(event_beacon_print);
}


void BEACON_commands() {
  COMM_check_command(String("BEACON_START"), BEACON_print_start);
  COMM_check_command(String("BEACON_STOP"), BEACON_print_stop);
}

#endif /* BEACON_H */
