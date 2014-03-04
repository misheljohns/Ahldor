/**************************************************************
  File:      Robot.ino 
  Contents:  This program runs the robot for the ME210 2014 
              Bitcoin Bonanza competition.
  
  Team:      Caitlin Clancy
             Stefan Kowalski
             Mishel Johns
             Hayk Martirosyan

**************************************************************/

/*---------------- Includes ---------------------------------*/

// outside libraries
#include <Servo.h>
#include "Timer.h"

// modules
#include "Defines.h"
#include "Communication.h"
#include "Multiplex.h"
#include "BeaconSens.h"
#include "Diagnostics.h"
#include "LineFind.h"
#include "MineShoot.h"
#include "DriveTrain.h"

/*---------------- Module Defines ---------------------------*/

// states
#define STATE_WAIT_FOR_JOYSTICK 0
#define STATE_WAIT_TO_START 1
#define STATE_ROTATE_TO_SERVER 2
#define STATE_FIND_THE_LINE 3
#define STATE_ROTATE_TO_ALIGN 4
#define STATE_FOLLOW_LINE 5
#define STATE_MINE_SHOOT 6
#define STATE_FIND_NEXT_EX 7
#define STATE_TURNOFF 8

/*------------------ Module Level Variables -----------------*/

// timer library object
Timer t;

// which state is the robot in
byte state;

/*---------------- Arduino Main Functions -------------------*/

void check_for_commands() {
  COMM_Update();
  if(COMM_has_new_command()) {
    DRIVE_commands();
    MINE_commands();
    BEACON_commands();
    DIAG_commands();
    LINE_commands();
    MUX_commands();
  }
}

void mine() {
  Serial.println("mined!");
}
int mine_timer;
void stopMine() {
  t.stop(mine_timer);
}

void setup() {
  
  // Initializing each module
  COMM_Init(&t);
  MUX_Init(&t);
  BEACON_Init(&t);
  DIAG_Init(&t);
  DRIVE_Init(&t);
  LINE_Init(&t);
  MINE_Init(&t);
  
  t.every(COMM_UPDATE_RATE, check_for_commands);
  
  //mine_timer = t.every(500, mine);
  //t.after(2600, stopMine);
  Serial.println("Modules initialized!");
  
  state = STATE_WAIT_TO_START;
  
  //state = STATE_FIND_THE_LINE; //for demo
}

void loop() {
  
  // Update the timer
  t.update();
  
  switch(state)
  {
    case STATE_WAIT_FOR_JOYSTICK:
      break;
    case STATE_WAIT_TO_START:
    
    //if startbutton pressed
          //selectside()
          
      break;
    case STATE_ROTATE_TO_SERVER:
      break;
    case STATE_FIND_THE_LINE:
      if(RearSensor())
      {
        state = STATE_ROTATE_TO_ALIGN;                
        digitalWrite(LWHEEL_ENABLE,LOW);
        digitalWrite(RWHEEL_ENABLE,LOW);
      }
      break;
    case STATE_ROTATE_TO_ALIGN:
    
    //if aligned
      RotateToShoot();//align for first target so we're ready to shot when we get to the server
      break;
    case STATE_FOLLOW_LINE:
      break;
    case STATE_MINE_SHOOT:
      break;
    case STATE_FIND_NEXT_EX:
      RotateToShoot();
      //delayMicroseconds();//time to finish turning
      break;
    case STATE_TURNOFF:
      //turn off all motors
      break;
  }
       
 
}
