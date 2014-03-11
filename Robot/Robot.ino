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

#define SERVER_TO_EXCHANGE_THRESHOLD 2000000

/*------------------ Module Level Variables -----------------*/

// timer library object
Timer t;

// which state is the robot in
byte state;

// if TRUE, beacon is to left and exchanges to right
// if FALSE, beacon is to right and exchanges to left
int map_left;


//count of button state
int server_cost;
int count_presses;

long t_previous = 0;

int beacon_type;

//map side detection
unsigned long travel_time;
unsigned long exchange_beacon_time;

int timeout_event;

int event_mine_coins = 0;
int event_shoot = 0;

int shooting = FALSE;

/*---------------- Arduino Main Functions -------------------*/

void MAIN_print_enable_switch() {
  Serial.println("Enable switch:" + String(MUX_read_digital(MUX_ENABLE_SWITCH)));
}

int MAIN_enable_switch() {
  return MUX_read_digital(MUX_ENABLE_SWITCH);
}

 void MAIN_commands() {
   COMM_check_command(String("FIND_LINE"), start_finding_line);
   COMM_check_command(String("ENABLED?"), MAIN_print_enable_switch);
   COMM_check_command(String("BEACON_SENSE"), start_beacon_sensing);
   COMM_check_command(String("START_MINING"), start_mining); 
 }
 
void check_for_commands() {
  COMM_Update();
  if(COMM_has_new_command()) {
    COMM_commands();
    DRIVE_commands();
    MINE_commands();
    BEACON_commands();
    LINE_commands();
    MUX_commands();
    MAIN_commands();
  }
}

void setup() {
  
  // Initializing each module
  COMM_Init(&t);
  MUX_Init(&t);
  BEACON_Init(&t);
  DRIVE_Init(&t);
  LINE_Init(&t);
  MINE_Init(&t);
  
  t.every(COMM_UPDATE_RATE, check_for_commands);
  
  Serial.println("Modules initialized!");
  
  state = STATE_WAIT_TO_START;
      
  //map_left = FALSE;
  
  map_left = -1;
  server_cost = 0;
  count_presses = 0;
  
  exchange_beacon_time = 0;
}

void start_finding_line() {
  Serial.println("Putting into STATE_FIND_THE_LINE!");
  DRIVE_forward(255);
  MINE_turn_servo(SERVO_POS_CENTER);
  state = STATE_FIND_THE_LINE;
}

void start_beacon_sensing() {
  Serial.println("Putting into STATE_ROTATE_TO_SERVER!");
  //MINE_turn_servo(SERVO_POS_CENTER + SERVO_FIND_BEACON_OFFSET);
  //delay(1000);
  DRIVE_turn_right(150);
  state = STATE_ROTATE_TO_SERVER;
}

void start_mining() {
  Serial.println("Putting into STATE_MINE_SHOOT!");

  DRIVE_stop();
  delay(20);
  
  state = STATE_MINE_SHOOT;
  server_cost = 1;
  count_presses = 0;
  MINE_coins();
}

void shoot_wrapper() {
  shooting = FALSE;
  MINE_shoot();
}

void MINE_coins() {
  if(count_presses < server_cost)
  {
    //press again
    MINE_button_push();
    count_presses += 1;
    
    //call to push again after 550s - Optimize this!
    t.after(BUTTON_PUSH_RATE, MINE_coins);
  }
  else
  {
    //we've pressed enough times, time to shoot now
    //it is already 550ms after the last push. Let's wait another second now.
    event_shoot = t.after(1000, shoot_wrapper);
    
    //run the coin pressing again, once shooting is done (2 sec wait)
    event_mine_coins = t.after(3000, MINE_coins);
    count_presses = 0;
    server_cost += 1;
    
    shooting = TRUE;
  }
}

void loop() {
  
  // Update the timer
  t.update();
  
  // Reset if enable switch ever pulled off
  if(!MAIN_enable_switch() && (state != STATE_WAIT_TO_START)) {
    COMM_reset();
  }
  
  switch(state)
  {
    case STATE_WAIT_TO_START:
      if(MAIN_enable_switch()) {
       start_beacon_sensing();
      } else {
        //Serial.println("Not enabled!");
      }
          
      break;
      
    case STATE_ROTATE_TO_SERVER:
      
      beacon_type = BeaconTypeDetected();
      if(map_left != -1)//if map side has already been set
      {
        if(beacon_type == SERVER_BEACON)
        {
          
          if(map_left == TRUE) {
            DRIVE_turn_right(255);
            delay(150);
            DRIVE_turn_left(255);
            delay(10);
          } else if (map_left == FALSE) {
            DRIVE_turn_left(255);
            delay(300);
            DRIVE_turn_right(255);
            delay(10);
          }
          
          DRIVE_stop();
  
          //map_left = FALSE;
          //MINE_select_side(map_left);
          
          start_finding_line();
        }
      }
      else //find out what side we are on
      {
        if(beacon_type == SERVER_BEACON)
        {
          if(exchange_beacon_time != 0)//other beacon has been detected in the past
          {
            //side select code
            travel_time = micros() - exchange_beacon_time;
            Serial.println("travel time: " + String(travel_time));
            
            DRIVE_stop();
            
            if(travel_time > SERVER_TO_EXCHANGE_THRESHOLD) {
              map_left = TRUE;
              Serial.println("Choosing map LEFT");
            } else {
              map_left = FALSE;
              Serial.println("Choosing map RIGHT");
            }
          }
        }
        else if(beacon_type == EXCHANGE_BEACON)
        {
          exchange_beacon_time = micros();
        }
      }
      break;
    
    case STATE_FIND_THE_LINE:
    
      if(LINE_front()) {   
        
        if(map_left == TRUE) {
          DRIVE_backward(255);
          delay(30);
        } else if (map_left == FALSE) {
          DRIVE_backward(255);
          delay(100);
        }
        
        DRIVE_stop();
        delay(100);
        
        if(map_left == TRUE) {
          DRIVE_turn_right(150);
        } else if (map_left == FALSE) {
          DRIVE_turn_left(150);
        }
        
        state = STATE_ROTATE_TO_ALIGN; 
      Serial.println("STATE_FIND_THE_LINE -> STATE_ROTATE_TO_ALIGN;");  
      }
      break;
      
    case STATE_ROTATE_TO_ALIGN:
      //Serial.println("front: " + String(MUX_read(MUX_FRONT_LINESENSOR)) + " back left: " + String(MUX_read(MUX_BACKL_LINESENSOR)) + " back right: " + String(MUX_read(MUX_BACKR_LINESENSOR)));
      if(LINE_back_left()&&LINE_back_right()) {
        
        // Counter-rotate for faster braking
        if(map_left == TRUE) {
          DRIVE_turn_left(255);
        } else if (map_left == FALSE) {
          DRIVE_turn_right(255);
        }
        delay(50);
        
        //DRIVE_stop();
        //delay(100000);
        state = STATE_FOLLOW_LINE;
        Serial.println("going to STATE_FOLLOW_LINE;");  
      }
      break;
      
      
    case STATE_FOLLOW_LINE:
      
      if(LINE_back_left() && LINE_back_right()) {
        DRIVE_backward_right(255);
        DRIVE_backward_left(255);
      } else if(!LINE_back_left() && LINE_back_right()) {
        DRIVE_backward_right(205);
        DRIVE_backward_left(255);
      } else if(!LINE_back_right() && LINE_back_left()) {
        DRIVE_backward_right(255);
        DRIVE_backward_left(205);
      } else {
        Serial.println("MISSED. OFF THE LINE!!!!");
        //the distance is short enough that we dont have to worry too much about the case where both sensors are off - hardcoding should work
      }
      
      //we've reached the promised land
      if(LINE_AtServer()) {
        start_mining();
      }
      
      break;
      
    case STATE_MINE_SHOOT:
      
      if(!LINE_back_left() || !LINE_back_right()) {
        Serial.println("Positioning off. Left: " + String(LINE_back_left()) + " Right: " + String(LINE_back_right()));
      }
      
      if(!LINE_AtServer()) {
        Serial.println("No longer pressed against wall!");
      }
      
      //////////////////////////////////////////////////////////////untested/////////////////////////////////
      if(BeaconTypeDetected() == 0) {
        
        t.stop(event_mine_coins);
        t.stop(event_shoot);
        
        MINE_rotate_to_shoot();
        
        
        
        ///rotate to next beacon, pause 
        
        //!!!!How do you clear timers when you set a t.after?
      }
    
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



