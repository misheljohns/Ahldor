/*---------------- Includes ---------------------------------*/

#if defined(ARDUINO) && ARDUINO >= 100 
#include "Arduino.h"  // if Arduino version 1.0 or later, include Arduino.h
#else
#include "WProgram.h"  // if Arduino version 22, include WProgram.h
#endif

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

/*------------------ Module Level Variables -----------------*/

Servo rotator;
byte exchangeSelect = 1;
unsigned int ex3,ex5,ex8;

/*---------------- Module Functions -------------------------*/

void InitMineShoot()
{
  rotator.attach(10);
  exchangeSelect = 1;
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

void RotateToShoot()
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


