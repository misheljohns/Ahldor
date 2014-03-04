/****************************************************
* Communication Module
* Prefix: COMM
****************************************************/

#ifndef COMM_H
#define COMM_H

/*---------------- Includes ---------------------------------*/

#include "Arduino.h"
#include "Timer.h"
#include "Defines.h"

/*---------------- Constants -------------------------*/

#define COMM_UPDATE_RATE 20

#define USB_BAUD 115200

#define END_COMMAND '\n'
#define DELIMITER ' '

#define NO_ARGUMENT -3333

/*---------------- Function Declarations -------------------------*/

void COMM_Init(Timer* t);
void COMM_Update();
void COMM_commands();

void COMM_send_command(String command);
void COMM_send_command(String command, int arg);

void COMM_send_usb_command(String command);
void COMM_send_usb_command(String command, int arg);

void COMM_check_command(String pCommand, void (*callback)(void));
void COMM_check_command(String pCommand, void (*callback)(int));

int COMM_has_new_command();
#endif /* COMM_H */
