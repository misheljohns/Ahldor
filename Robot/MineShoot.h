/****************************************************
 * Mining and shooting
 * Prefix: MINE
 ****************************************************/
 
#ifndef MINE_H
#define MINE_H

/*---------------- Includes ---------------------------------*/

#include "Arduino.h"
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

#define BUTTON_IN 90
#define BUTTON_OUT 150

/*------------------ Module Level Variables -----------------*/

Servo rotator;
Servo miner;

byte exchangeSelect;
unsigned int ex3,ex5,ex8;

static Timer* timer;
int event_button_push;

// Desired servo position, used for sweeping the servo
int desired_servo_pos;
int current_servo_pos;

//number of pushes
int button_presses;

/*---------------- Module Functions -------------------------*/

void MINE_servo_write(int microseconds) {
  rotator.writeMicroseconds(microseconds);
}

void MINE_turn_servo(int pos) {
  desired_servo_pos = pos; 
  Serial.println("New turning servo position: " + String(pos));
}

void MINE_update_servo() {
  if(desired_servo_pos > current_servo_pos) current_servo_pos += 1;
  if(desired_servo_pos < current_servo_pos) current_servo_pos -= 1;
  MINE_servo_write(current_servo_pos);
}

void MINE_has_coin() {
  
}

void MINE_button_release() {
  Serial.println("Button released!");
  miner.write(BUTTON_OUT);
  
}

void MINE_button_push() {
  Serial.println("Button pushed!");
  miner.write(BUTTON_IN);
  button_presses += 1;
  timer->after(BUTTON_OUT_TIME, MINE_button_release);
}

int MINE_button_presses() {
  return button_presses;
}

void MINE_start_pushing_button() {
  event_button_push = timer->every(BUTTON_PUSH_RATE, MINE_button_push);
}

void MINE_stop_pushing_button() {
  timer->stop(event_button_push);
}

void MINE_selectside(byte a)
{
  if(a)
 {
   ex3 = EXCHANGE_3_ROT_A;
   ex5 = EXCHANGE_5_ROT_A;
   ex8 = EXCHANGE_8_ROT_A;
 }
 else
 {
   ex3 = EXCHANGE_3_ROT_B;
   ex5 = EXCHANGE_5_ROT_B;
   ex8 = EXCHANGE_8_ROT_B;
 }
}


void MINE_stop_shoot() {
  digitalWrite(SHOOTER, LOW);
}

void MINE_shoot() {
  digitalWrite(SHOOTER, HIGH);
  timer->after(SHOOT_TIME, MINE_stop_shoot);
}


void MINE_rotate_to_shoot()
{
  switch(exchangeSelect)
  {
    case EXCHANGE_3:
      MINE_turn_servo(ex3);
      break;
    case EXCHANGE_5:
      MINE_turn_servo(ex5);
      break;
    case EXCHANGE_8:
      MINE_turn_servo(ex8);
      break;
    case 4:
      //all exchanges down
      //victory code here (hopefully)
      break;
  }
  exchangeSelect = exchangeSelect + 1;
}

void MINE_Init(Timer* t) {
  
  timer = t;
  
  pinMode(SHOOTER, OUTPUT);
  
  rotator.attach(ROTATOR);
  current_servo_pos = SERVO_POS_CENTER;
  desired_servo_pos = current_servo_pos;
  
  miner.attach(MINER);
  miner.write(BUTTON_OUT);
  
  exchangeSelect = 1;
  button_presses = 0;
  
  t->every(SERVO_UPDATE_RATE, MINE_update_servo);
  
  Serial.println("MINE module initialized!");
}

void MINE_commands() {
  COMM_check_command(String("MINE_PUSH_BUTTON"), MINE_button_push);
  COMM_check_command(String("START_PUSHING_BUTTON"), MINE_start_pushing_button);
  COMM_check_command(String("STOP_PUSHING_BUTTON"), MINE_stop_pushing_button);
  
  COMM_check_command(String("SERVO"), MINE_turn_servo);
  
  COMM_check_command(String("SHOOT"), MINE_shoot);
  COMM_check_command(String("STOP_SHOOT"), MINE_stop_shoot);
}

#endif /* MINE_H */
