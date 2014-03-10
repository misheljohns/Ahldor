/****************************************************
 * Beacon Sensing
 * Prefix: BEACON
 ****************************************************/


/*---------------- Includes ---------------------------------*/

#include "BeaconSens.h"

/*---------------- Module Functions -------------------------*/

unsigned long time;
volatile unsigned long time2;
volatile int count1;
double freq;
byte inLine;
static Timer* timer_beacon;

int event_beacon_print;

void count()
{
  switch(count1++)
  {
    case 20:
      time2 = micros();
      break;
    case 0:
      time = micros();
      break;
  }
  //inLine = 1;
}

/* not using this anymore
byte BEACON_IsInLine()
{
  byte tmp = inLine;
  inLine = 0;
  return tmp;
}
*/

void InitFreqMeasure()
{
  Serial.println("Freq measure init!");
  pinMode(2, INPUT);
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
    freq = ((double)20000)/(double)(time2 - time);
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
    freq = ((double)20000)/(double)(time2 - time);
    time2 = 0; 
    count1 = 0;
    if((freq > 2.9) && (freq < 3.1))
      return EXCHANGE_BEACON;
    else if((freq > 0.75) && (freq < 0.95))
      return SERVER_BEACON;
    else 
      return UNKNOWN_BEACON_FREQ;
    }
  else return 0;
}

//so that a few random innterrupt triggers while rotating can be cleared
void ResetFreqMeasure()
{
  freq = 0;
  count1 = 0;
  time2 = 0; 
}

void StopFreqMeasure()
{
  detachInterrupt(0);  
}

void BEACON_Init(Timer* t) {
  Serial.println("BEACON module initialized!");
  InitFreqMeasure();
  
  timer_beacon = t;
}

void BEACON_print_raw() {
  Serial.print("BEACON TYPE ");
  Serial.print(BeaconTypeDetected());
  Serial.print(" has FREQ ");
  Serial.println(GetFreq());
}

void BEACON_print_start() {
  //MUX_print_stop();
  Serial.println("Beacon start!");
  event_beacon_print = timer_beacon->every(100, BEACON_print_raw);
}

void BEACON_print_stop() {
  timer_beacon->stop(event_beacon_print);
}

void BEACON_commands() {
  COMM_check_command(String("BEACON_START"), BEACON_print_start);
  COMM_check_command(String("BEACON_STOP"), BEACON_print_stop);
}

