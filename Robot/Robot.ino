/**************************************************************
  File:      Robot.ino 
  Contents:  This program runs the robot for the ME210 2014 
              Bitcoin Bonanza competition.
  Notes:    Target: Arduino UNO R2
            Arduino IDE version: 1.0.5
  
  
**************************************************************/

/*---------------- Includes ---------------------------------*/

#include "Defines.h"
#include "BeaconSens.h"
#include "Diagnostics.h"
#include "Multiplex.h"
#include "LineFind.h"
#include "MineShoot.h"

#include <Servo.h>//because apparently even though this is used in another file, it still needs to be here for the arduino compiler to find it

/*---------------- Module Defines ---------------------------*/

//states
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

byte state;

/*---------------- Arduino Main Functions -------------------*/
void setup() {  // setup() function required for Arduino
 
  InitMux();
  
  //for debug stuff
  Serial.begin(9600);
  Serial.println("Starting Intimidator.");
   
  //state = STATE_WAIT_TO_START;
  
  state = STATE_FIND_THE_LINE; //for demo
}

void loop() {  // loop() function required for Arduino  
  
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

/*---------------- Module Functions -------------------------*/




