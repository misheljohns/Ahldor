#include <Servo.h>
#include "Timer.h"


String usb_rx_buffer = "";
volatile int count1;
volatile unsigned long time, time2;
Timer t;

void setup()
{
  Serial.begin(115200);
  Serial.println("starting....");
  InitFreqMeasure();
  t.every(20, check_for_commands);
}

void loop()
{
    t.update();
}

void check_for_commands()
{
  if(Serial.available())
  {
    char c = Serial.read();
    Serial.println(String(c));
    usb_rx_buffer = usb_rx_buffer + c;
    Serial.println(usb_rx_buffer);    
    Serial.println(usb_rx_buffer.indexOf('\n'));
  }
}

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
}

void InitFreqMeasure()
{
  pinMode(2, INPUT);
  attachInterrupt(0, count, RISING);
  count1 = 0;
}
  
