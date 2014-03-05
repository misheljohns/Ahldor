/****************************************************
 * Global definitions
 * Prefix: DEFINES
 ****************************************************/

#ifndef DEFINES_H
#define DEFINES_H

#include "Arduino.h"

//debug
#define DEBUG

#ifdef DEBUG
  #define DEBUG_PRINT(x)  Serial.println (x)
  #define DEBUG_TIME()  time = micros();
#else
  #define DEBUG_PRINT(x)
  #define DEBUG_TIME()
#endif

#define TRUE 1
#define FALSE 0

#define BEACON_INTERRUPT 2

// DriveTrain pins
#define RWHEEL_DIR 4
#define RWHEEL_ENABLE 3
//#define LWHEEL_BRAKE 9
#define LWHEEL_DIR 7
#define LWHEEL_ENABLE 5
//#define RWHEEL_BRAKE 8

// MineShoot pins
#define ROTATOR 6
#define SHOOTER 9
#define MINER_DIR 10
#define MINER_ENABLE 11

//Mux pins
#define MUX_S0 A0
#define MUX_S1 A1
#define MUX_S2 A2
#define MUX_S3 A3
#define MUX_IN A4

// Mux input pins (not Arduino pins)
#define MUX_MAP_SIDE_SWITCH ?
#define MUX_ENABLE_SWITCH ?
#define MUX_COIN_SENSOR ?
#define MUX_FRONT_LINESENSOR 4
#define MUX_BACKL_LINESENSOR 5
#define MUX_BACKR_LINESENSOR 6
#define MUX_WALL_SWITCH_LEFT 9
#define MUX_WALL_SWITCH_RIGHT 10
#define MUX_BEACON_LEFT 11
#define MUX_BEACON_RIGHT 12

// Beacon frequency (not pins)
#define SERVER_BEACON 0
#define EXCHANGE_BEACON 1

/*---------------- Module Functions -------------------------*/


#endif /* DEFINES_H */


