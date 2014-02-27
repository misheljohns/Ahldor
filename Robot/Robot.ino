/**************************************************************
  File:      Robot.ino 
  Contents:  This program runs the robot for the ME210 2014 
              Bitcoin Bonanza competition.
  Notes:    Target: Arduino UNO R2
            Arduino IDE version: 1.0.5
  
  
**************************************************************/

/*---------------- Includes ---------------------------------*/

#include <Servo.h>

/*---------------- Module Defines ---------------------------*/

//debug
#define DEBUG

#ifdef DEBUG
  #define DEBUG_PRINT(x)  Serial.println (x)
  #define DEBUG_TIME()  time = micros();
#else
  #define DEBUG_PRINT(x)
  #define DEBUG_TIME()
#endif


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

//pins

#define LWHEEL_DIR 12
#define LWHEEL_ENABLE 3
#define LWHEEL_BRAKE 9
#define RWHEEL_DIR 13
#define RWHEEL_ENABLE 11
#define RWHEEL_BRAKE 8

#define ROTATOR 10
#define SHOOTER 6
#define MINER 5

// free for now - pins 4,7




/*------------------ Module Level Variables -----------------*/

unsigned long time;
byte state;

/*---------------- Arduino Main Functions -------------------*/
void setup() {  // setup() function required for Arduino
 
  InitMux();
  
  //for debug stuff
  Serial.begin(9600);
  Serial.println("Starting Intimidator.");
  time = micros();
   
  state = STATE_WAIT_TO_START;
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




