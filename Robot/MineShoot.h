/****************************************************
 * Mining and shooting
 * Prefix: MINE
 ****************************************************/
 
#ifndef MINE_H
#define MINE_H

/*---------------- Includes ---------------------------------*/

#include "Arduino.h"
#include "Timer.h"
#include "Communication.h"
#include "Defines.h"
#include <Servo.h>

/*---------------- Module Defines ---------------------------*/

//Servo angles
#define FIND_BEACON_OFFSET 100 //the angle at which the top should be rotated to point at the beacon when rotating initially,so that the bot points towards the line

#define EXCHANGE_8_ROT_A 1500
#define EXCHANGE_5_ROT_A 1700
#define EXCHANGE_3_ROT_A 1200

#define EXCHANGE_8_ROT_B 1500
#define EXCHANGE_5_ROT_B 1700
#define EXCHANGE_3_ROT_B 1200  

//order of shooting
///doing 8 first for the checkoff
#define EXCHANGE_3 3
#define EXCHANGE_5 2
#define EXCHANGE_8 1

// How often to push the button
#define BUTTON_PUSH_RATE 550

// How long after pushing in the button to pull out
#define BUTTON_OUT_TIME 200

#define SERVO_POS_CENTER 1500
#define SERVO_POS_3_EXCHANGE 1700
#define SERVO_POS_5_EXCHANGE 1250
#define SERVO_POS_8_EXCHANGE 1500

#define SERVO_UPDATE_RATE 3

#define SHOOT_TIME 1000

#define BUTTON_IN 115
#define BUTTON_OUT 150

/*---------------- Module Functions -------------------------*/

void MINE_servo_write(int microseconds);
void MINE_turn_servo(int pos);
void MINE_update_servo();
void MINE_has_coin();
void MINE_button_release();
void MINE_button_push();
int MINE_button_presses();
void MINE_start_pushing_button();
void MINE_stop_pushing_button();
void MINE_selectside(byte a);
void MINE_stop_shoot();
void MINE_shoot();
void MINE_rotate_to_shoot();
void MINE_Init(Timer* t);
void MINE_commands();

#endif /* MINE_H */
