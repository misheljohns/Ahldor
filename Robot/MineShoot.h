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
#define EXCHANGE_3 1
#define EXCHANGE_5 2
#define EXCHANGE_8 3

// How often to push the button
#define BUTTON_PUSH_RATE 550

// How long after pushing in the button to pull out
#define BUTTON_OUT_TIME 200

/*------------------ Module Level Variables -----------------*/

Servo rotator;
byte exchangeSelect = 1;
unsigned int ex3,ex5,ex8;

static Timer* timer;
int event_button_push;

/*---------------- Module Functions -------------------------*/


void MINE_button_release() {
  Serial.println("Button released!");
  digitalWrite(MINER_DIR, HIGH);
  analogWrite(MINER_ENABLE, 50);
}

void MINE_button_push() {
  Serial.println("Button pushed!");
  digitalWrite(MINER_DIR, LOW);
  analogWrite(MINER_ENABLE, 50);
  timer->after(BUTTON_OUT_TIME, MINE_button_release);
}

void MINE_start_pushing_button() {
  event_button_push = timer->every(BUTTON_PUSH_RATE, MINE_button_push);
}

void MINE_stop_pushing_button() {
  timer->stop(event_button_push);
}

void selectside(byte a)
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

void MINE_servo_write(int microseconds) {
  Serial.println("Writing to servo: " + String(microseconds));
  rotator.writeMicroseconds(microseconds);
}

void MINE_shoot() {
  digitalWrite(SHOOTER, HIGH);
}

void MINE_stop_shoot() {
  digitalWrite(SHOOTER, LOW);
}

void MINE_rotate_to_shoot()
{
  switch(exchangeSelect)
  {
    case EXCHANGE_3:
      rotator.writeMicroseconds(ex3);
      break;
    case EXCHANGE_5:
      rotator.writeMicroseconds(ex5);
      break;
    case EXCHANGE_8:
      rotator.writeMicroseconds(ex8);
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
  
  rotator.attach(ROTATOR);
  exchangeSelect = 1;
  
  pinMode(SHOOTER, OUTPUT);
  pinMode(MINER_DIR, OUTPUT);
  pinMode(MINER_ENABLE, OUTPUT);
  
  Serial.println("MINE module initialized!");
}

void MINE_commands() {
  COMM_check_command(String("MINE_PUSH_BUTTON"), MINE_button_push);
  COMM_check_command(String("START_PUSHING_BUTTON"), MINE_start_pushing_button);
  COMM_check_command(String("STOP_PUSHING_BUTTON"), MINE_stop_pushing_button);
  
  COMM_check_command(String("SERVO"), MINE_servo_write);
  
  COMM_check_command(String("SHOOT"), MINE_shoot);
  COMM_check_command(String("STOP_SHOOT"), MINE_stop_shoot);
}

#endif /* MINE_H */
