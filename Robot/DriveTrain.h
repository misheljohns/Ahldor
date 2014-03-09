/****************************************************
 * Drivetrain
 * Prefix: Drive
 ****************************************************/
 
#ifndef DRIVE_H
#define DRIVE_H

/*---------------- Includes ---------------------------------*/

#include "Arduino.h"
#include "Timer.h"
#include "Defines.h"
#include "Communication.h"

/*---------------- Module Constants -------------------------*/

#define LEFT_OFFSET 0
#define RIGHT_OFFSET 0

/*---------------- Module Functions -------------------------*/

int clamp_v(int vel);
void DRIVE_forward_left(int vel);
void DRIVE_forward_right(int vel);
void DRIVE_backward_left(int vel);
void DRIVE_backward_right(int vel);
void DRIVE_forward(int vel);
void DRIVE_backward(int vel);
void DRIVE_turn_right(int mag);
void DRIVE_turn_left(int mag);
void DRIVE_stop();
void DRIVE_forward_full();
void DRIVE_backward_full();
void DRIVE_Init(Timer* t);
void DRIVE_commands();



#endif /* DRIVE_H */
