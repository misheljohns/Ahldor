/****************************************************
 * Diagnostics
 * Prefix: DIAG
 ****************************************************/

#ifndef DIAG_H
#define DIAG_H

/*---------------- Includes ---------------------------------*/

#include "Arduino.h"
#include "Defines.h"

/*---------------- Module Functions -------------------------*/

void DIAG_Init(Timer* t) {
  Serial.println("DIAG module initialized!");
}

void DIAG_commands() {
  
}

#endif /* DIAG_H */
