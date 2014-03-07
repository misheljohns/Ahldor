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

// if TRUE, beacon is to left and exchanges to right
// if FALSE, beacon is to right and exchanges to left
int map_left;

long t_previous = 0;

/*---------------- Arduino Main Functions -------------------*/

 void MAIN_commands() {
   COMM_check_command(String("FIND_LINE"), start_finding_line);
   COMM_check_command(String("BEACON_SENSE"), start_beacon_sensing);
 }
 
void check_for_commands() {
  COMM_Update();
  if(COMM_has_new_command()) {
    COMM_commands();
    DRIVE_commands();
    MINE_commands();
    BEACON_commands();
    DIAG_commands();
    LINE_commands();
    MUX_commands();
    MAIN_commands();
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
}

// temp, for line following
void start_finding_line() {
  map_left = FALSE;
  Serial.println("Putting into STATE_FIND_THE_LINE!");
  DRIVE_forward(255);
  state = STATE_FIND_THE_LINE;
}

// temp, for rotating to find the beacon and calculate side
void start_beacon_sensing() {
  Serial.println("Putting into STATE_ROTATE_TO_SERVER!");
  //DRIVE_forward(255);
  DRIVE_turn_right(80);
  state = STATE_ROTATE_TO_SERVER;
  InitFreqMeasure();  
}

void loop() {
  //MUX_print_line();
  // Update the timer
  t.update();
  
  switch(state)
  {
    case STATE_WAIT_TO_START:
    
    //if startbutton pressed
          //selectside()
          
      break;
    case STATE_ROTATE_TO_SERVER:
      if(IsInLine())
      {
        
        // Counter-rotate for faster braking
        DRIVE_turn_left(255);
        delay(1);
        //Serial.println("inline and reversed, :" + String(IsInLine()));
        DRIVE_stop();
        delay(100);
        Serial.println("inline and reversed, stopped, 100 later :" + String(IsInLine()));
        
        //test, in the final code we'll have to test what beacon
        state = TURNOFF;
        /*
        map_left = FALSE;
        Serial.println("Putting into STATE_FIND_THE_LINE!");
        DRIVE_forward(255);
        state = STATE_FIND_THE_LINE;
        */
      }
        

      break;
    case STATE_FIND_THE_LINE:
    
      if(LINE_front()) {             
        DRIVE_backward(255);
        delay(60);
        DRIVE_stop();
        delay(100);
        
        if(map_left == TRUE) {
          DRIVE_turn_right(100);
        } else if (map_left == FALSE) {
          DRIVE_turn_left(100);
        }
      
        state = STATE_ROTATE_TO_ALIGN; 
      Serial.println("going to STATE_ROTATE_TO_ALIGN;");  
      }
      break;
    case STATE_ROTATE_TO_ALIGN:
      Serial.println("front: " + String(MUX_read(MUX_FRONT_LINESENSOR)) + " back left: " + String(MUX_read(MUX_BACKL_LINESENSOR)) + " back right: " + String(MUX_read(MUX_BACKR_LINESENSOR)));
      if(LINE_back_left()&&LINE_back_right()) {
        
        ///////////////////////////////////////////////////////////////////////Hayk, we shoudl remove this, why do we stop before we counter-rotate? we sould just directly counter rotate, that's faster.
        DRIVE_stop();
        delay(100);
        
        // Counter-rotate for faster braking
        if(map_left == TRUE) {
          DRIVE_turn_left(255);
        } else if (map_left == FALSE) {
          DRIVE_turn_right(255);
        }
        delay(100);
        
        DRIVE_backward(120);
        state = STATE_FOLLOW_LINE;
        Serial.println("going to STATE_FOLLOW_LINE;");  
      }
      
      static long dt = micros() - t_previous;
      Serial.println(dt);
      t_previous = micros();
      
      //if aligned
      //MINE_rotate_to_shoot();//align for first target so we're ready to shot when we get to the server
      break;
    case STATE_FOLLOW_LINE:
      
      /*
      static int vel = 120;
      static int turn_mag = 0;
      
      if(!LINE_back_left()) turn_mag += 1;
      if(!LINE_back_right()) turn_mag -= 1;
      
      if(!LINE_back_left() && !LINE_back_right()) {
        Serial.println("Off the line!");
      }
      
      DRIVE_backward_left(vel - turn_mag);
      DRIVE_backward_right(vel + turn_mag);
      Serial.println("back left: " + String(LINE_back_left()) + " back right: " + String(LINE_back_right()) + " Vel: " + String(vel) + " turn mag: " + String(turn_mag));
      */
      
      if(LINE_back_left() && LINE_back_right()) {
        DRIVE_backward_right(255);
        DRIVE_backward_left(255);
      } if(!LINE_back_left()) {
        DRIVE_backward_right(225);
        DRIVE_backward_left(255);
      } else if(!LINE_back_right()) {
        DRIVE_backward_right(255);
        DRIVE_backward_left(225);
      } else {
        Serial.println("MISSED OFF THE LINE!!!!");
      }
      
      delay(10);
      //add stuff to compensate for angle off, and for case where both sensors are off
      
      
      break;
    case STATE_MINE_SHOOT:
      break;
    case STATE_FIND_NEXT_EX:
      MINE_rotate_to_shoot();
      //delayMicroseconds();//time to finish turning
      break;
    case STATE_TURNOFF:
      //turn off all motors
      break;
  }
       
}



