/****************************************************
 * Command Parser (used for debugging)
 * Prefix: CMD
 ****************************************************/

#ifndef CMD_H
#define CMD_H

/*---------------- Includes ---------------------------------*/

#include "Arduino.h"
#include "Defines.h"

/*---------------- Constants -------------------------*/

#define CMD_DELIMITER ' '
#define CMD_UPDATE_RATE 100

/*---------------- Private Variables -------------------------*/

static String serial_received = String();

/*---------------- Private Functions -------------------------*/

static int CMD_new_serial_data() {
  if (serial_received.length() > 0)
    return TRUE;
  return FALSE;
}

static void CMD_read_serial() {
  
  serial_received = String();
  
  if (Serial.available()) {
    
    while(Serial.available())
      serial_received += (char)Serial.read();
    
    Serial.print("Received: ");
    Serial.println(serial_received);
  }
}

static int CMD_check_command_string(String* pStr) {
  
  // No new data
  if (!CMD_new_serial_data())
    return FALSE;
  
  String command = *pStr;
  
  // Serial received is too short to be this command
  if (serial_received.length() < command.length())
    return FALSE;
  
  // Make sure all the characters match up
  int i;
  for(i = 0; i < command.length(); i++) {
     if(serial_received[i] != command[i])
         return FALSE;
  }
  
  // Make sure if there are more characters, that the next one is a space
  if (serial_received.length() > command.length())
    if (serial_received[command.length()] != CMD_DELIMITER)
      return FALSE;
  
  // Matched up
  return TRUE;
}


/*---------------- Public Functions -------------------------*/

void CMD_Init() {
  
}

void CMD_check_command(String pCommand, void (*callback)(void)) {
  
  if(CMD_check_command_string(&pCommand))
    callback();
}

void CMD_Update() {
  
  // Update serial_received
  CMD_read_serial();
  
  // Commands for CMD module
  //CMD_check_command(String("CMD_TEST"), CMD_test);  
}

#endif /* CMD_H */
