/****************************************************
 * Beacon Sensing
 * Prefix: BEACON
 ****************************************************/

#ifndef BEACON_H
#define BEACON_H

/*---------------- Includes ---------------------------------*/

#include "Arduino.h"
#include "Defines.h"
#include "Timer.h"
#include "Communication.h"

/*--------------------- Constants ---------------------------*/

#define PULSE_COUNT 20

/*---------------- Module Functions -------------------------*/

void count();
//byte BEACON_IsInLine();
void InitFreqMeasure();
double GetFreq();
byte BeaconDetected();
byte BeaconTypeDetected();
void StopFreqMeasure();
void BEACON_Init(Timer* t);
void BEACON_print_raw();
void BEACON_print_start();
void BEACON_print_stop();
void BEACON_commands();

#endif /* BEACON_H */
