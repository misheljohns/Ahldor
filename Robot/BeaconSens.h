/*---------------- Includes ---------------------------------*/

#if defined(ARDUINO) && ARDUINO >= 100 
#include "Arduino.h"  // if Arduino version 1.0 or later, include Arduino.h
#else
#include "WProgram.h"  // if Arduino version 22, include WProgram.h
#endif

#include "Defines.h"


/*---------------- Module Functions -------------------------*/

unsigned long time;
volatile unsigned long time2;
volatile int count1;
double freq;

void count()
{
  switch(count1++)
  {
    case 100:
      time2 = micros();
      break;
    case 0:
      time2 = micros();
      break;
  }
}

void InitFreqMeasure()
{
  pinMode(2, INPUT);
  time = micros();
  attachInterrupt(0, count, RISING);
  count1 = 0;
}

double GetFreq()
{
  return freq;
}

byte BeaconDetected()
{
  if(time2 != 0)
  {
    freq = ((double)100000)/(double)(time2 - time);
    time2 = 0; 
    count1 = 0;
    return 1;
  }
  else return 0;
}

byte BeaconTypeDetected()
{
  if(time2 != 0)
  {
    freq = ((double)100000)/(double)(time2 - time);
    time2 = 0; 
    count1 = 0;
    if((freq > 2.9) && (freq < 3.1))
      return SERVER_BEACON;
    else if((freq > 0.75) && (freq < 0.95))
      return EXCHANGE_BEACON;
  }
  else return 0;
}

void StopFreqMeasure()
{
  detachInterrupt(0);
}


