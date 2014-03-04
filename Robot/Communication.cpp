/****************************************************
* Communication Module
* Prefix: COMM
****************************************************/

/*---------------- Includes ---------------------------------*/

#include "Communication.h"

/*---------------- Private Variables -------------------------*/

String usb_rx_buffer = "";

String last_command = String();
int last_arg = -1;

int new_command = FALSE;

/*---------------- Private Functions -------------------------*/

int COMM_has_new_command() {
  return new_command;
}

static int COMM_check_command_string(String* pStr) {
  
  String command = *pStr;
  
  if (command == last_command)
    return TRUE;
  return FALSE;
}

static void COMM_check_all_commands() {
  //DRIVE_commands();
}

static void COMM_command_received(String command) {
  //Serial.println("COMM command received: " + command);
  last_command = command;
  last_command.toUpperCase();
  last_arg = NO_ARGUMENT;
  new_command = TRUE;
  //COMM_check_all_commands();
}

static void COMM_command_received(String command, int arg) {
  //Serial.println("COMM command received: " + command + ", arg: " + String(arg));
  last_command = command;
  last_command.toUpperCase();
  last_arg = arg;
  new_command = TRUE;
  //COMM_check_all_commands();
}

static void COMM_parse_command(String command) {
  Serial.println("Command received: " + command);
  
  int delimiter_index = command.indexOf(DELIMITER);
  if(delimiter_index != -1) {
    String command_name = command.substring(0, delimiter_index);
    String arg_str = command.substring(delimiter_index+1);
      int arg = arg_str.toInt();
      if ((arg == 0) && (arg_str != "0")) {
        Serial.println("Integer argument converted to zero, ignoring!!");
        COMM_send_usb_command("ERROR bad command argument, not int");
      } else
        COMM_command_received(command_name, arg);
  } else {
    COMM_command_received(command);
  }
}

static void COMM_reset() {
  Serial.println("COMM module reset!");
}

void COMM_check_command(String pCommand, void (*callback)(void)) {
  
  if(last_arg != NO_ARGUMENT) {
    //Serial.println("Ignoring command, argument present!");
    return;
  }
  
  if(COMM_check_command_string(&pCommand))
    callback();
}

void COMM_check_command(String pCommand, void (*callback)(int)) {
  
  if(last_arg == NO_ARGUMENT) {
    return;
  }
  
  if(COMM_check_command_string(&pCommand))
    callback(last_arg);
}

void COMM_send_usb_command(String command) {
  Serial.print(command);
  Serial.print(END_COMMAND);
}

void COMM_send_usb_command(String command, int arg) {
  Serial.print(command);
  Serial.print(DELIMITER);
  Serial.print(arg);
  Serial.print(END_COMMAND);
}

void COMM_Update() {
  
  new_command = FALSE;
  
  if(Serial.available()) {
    usb_rx_buffer = usb_rx_buffer + String((char)Serial.read());
    //Serial.println("USB buffer increased: " + usb_rx_buffer);
    
    int end_command_index = usb_rx_buffer.indexOf(END_COMMAND);
    
    if(end_command_index != -1) {
      String command = usb_rx_buffer.substring(0, end_command_index);
      usb_rx_buffer = usb_rx_buffer.substring(end_command_index+1);
      COMM_parse_command(command);
    }
  }
}

void COMM_Init() {
  
  Serial.begin(USB_BAUD);
  
  Serial.println("COMM module initialized!");
}

void COMM_commands() {
  
  // Commands
  //COMM_check_command(String("RESET"), COMM_reset);
}
