/**************************************************************
  File:      Robot.ino 
  Contents:  This program runs the robot for the ME210 2014 
              Bitcoin Bonanza competition.
  Notes:    Target: Arduino UNO R2
            Arduino IDE version: 1.0.5
  
  
**************************************************************/

/*---------------- Includes ---------------------------------*/



/*---------------- Module Defines ---------------------------*/

//debug
//#define DEBUGMODE 1

//states

#define STATE_WAIT_TO_START 0
#define STATE_FIND_THE_LINE 0
#define STATE_FOLLOW_LINE 1
#define STATE_TURNRIGHT 2

//pins

#define LWHEEL_DIR 12
#define LWHEEL_ENABLE 3
#define LWHEEL_BRAKE 9
#define RWHEEL_DIR 13
#define RWHEEL_ENABLE 11
#define RWHEEL_BRAKE 8

#define ROTATOR 5
#define SHOOTER 6
#define MINER 10

#define MUX_IN A0
#define MUX_SET0 A1
#define MUX_SET1 A2
#define MUX_SET2 A3
#define MUX_SET3 A4

// free for now - pins 4,7

/*------------------ Module Level Variables -----------------*/


//#ifdef DEBUGMODE
unsigned long time;
//#endif
unsigned char state;

/*---------------- Arduino Main Functions -------------------*/
void setup() {  // setup() function required for Arduino
 
  //#ifdef DEBUGMODE
  Serial.begin(9600);
  Serial.println("Starting...");
  time = micros();
  //#endif
  
  
  state = STATE_WAIT_TO_START;
  
  //time = micros();
  digitalWrite(2,LOW);
  analogWrite(3,100);
  digitalWrite(4,HIGH);
  analogWrite(5,100);
  
}

void loop() {  // loop() function required for Arduino
  int right  = analogRead(0);
  int left = analogRead(1);
  
  
  switch(state)
  {
    case STATE_WAIT_TO_START:
      break;
  }
  
  
  Serial.print(left);
  Serial.print("  ");
  Serial.println(right);    
      
 
}

/*---------------- Module Functions -------------------------*/




