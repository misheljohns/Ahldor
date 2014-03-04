/****************************************************
 * Drivetrain
 * Prefix: Drive
 ****************************************************/
 
#ifndef DRIVE_H
#define DRIVE_H

/*---------------- Includes ---------------------------------*/

#include "Arduino.h"
#include "Defines.h"
#include "Communication.h"

/*---------------- Module Functions -------------------------*/

void InitMotors()
{
  //brakes off
  PORTB = PORTB & B11111100;//PB0 and PB1 set to LOW
}

void BrakeMotors()
{
  PORTB = PORTB | B00000011;//PB0 and PB1 set to HIGH
}

void DRIVE_forward_left(int vel) {
  Serial.println("Left wheel forward at vel " + String(vel));
  digitalWrite(LWHEEL_DIR, HIGH);
  analogWrite(LWHEEL_ENABLE, vel);
}

void DRIVE_forward_right(int vel) {
  Serial.println("Right wheel forward at vel " + String(vel));
  digitalWrite(RWHEEL_DIR, LOW);
  analogWrite(RWHEEL_ENABLE, vel);
}

void DRIVE_backward_left(int vel) {
  Serial.println("Left wheel backward at vel " + String(vel));
  digitalWrite(LWHEEL_DIR, LOW);
  analogWrite(LWHEEL_ENABLE, vel);
}

void DRIVE_backward_right(int vel) {
  Serial.println("Right wheel forward at vel " + String(vel));
  digitalWrite(RWHEEL_DIR, HIGH);
  analogWrite(RWHEEL_ENABLE, vel);
}

void DRIVE_forward(int vel) {
  DRIVE_forward_left(vel);
  DRIVE_forward_right(vel);
}

void DRIVE_backward(int vel) {
  DRIVE_backward_left(vel);
  DRIVE_backward_right(vel);
}

void DRIVE_stop() {
  DRIVE_forward(0);
}

void DRIVE_forward_full() {
  DRIVE_forward_left(255);
  DRIVE_forward_right(255);
}

void DRIVE_backward_full() {
  DRIVE_backward_left(255);
  DRIVE_backward_right(255);
}

void DRIVE_Init() {
  
  pinMode(LWHEEL_DIR, OUTPUT);
  pinMode(RWHEEL_DIR, OUTPUT);
  pinMode(LWHEEL_ENABLE, OUTPUT);
  pinMode(RWHEEL_ENABLE, OUTPUT);
  pinMode(LWHEEL_BRAKE, OUTPUT);
  pinMode(RWHEEL_BRAKE, OUTPUT);
  
  digitalWrite(LWHEEL_DIR, LOW);
  digitalWrite(RWHEEL_DIR, LOW);
  analogWrite(LWHEEL_ENABLE, 0);
  analogWrite(RWHEEL_ENABLE, 0);
  digitalWrite(LWHEEL_BRAKE, LOW);
  digitalWrite(RWHEEL_BRAKE, LOW);
  
  Serial.println("DRIVE module initialized!");
}

void DRIVE_commands() {
  
  // Commands
  COMM_check_command(String("DRIVE_STOP"), DRIVE_stop);
  COMM_check_command(String("DRIVE_FORWARD_FULL"), DRIVE_forward_full);
  COMM_check_command(String("DRIVE_BACKWARD_FULL"), DRIVE_backward_full);
  COMM_check_command(String("DRIVE_FORWARD"), DRIVE_forward);
  COMM_check_command(String("DRIVE_BACKWARD"), DRIVE_backward);
}

#endif /* DRIVE_H */

