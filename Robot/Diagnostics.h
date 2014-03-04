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

void DIAG_Init() {
  Serial.println("DIAG module initialized!");
}

#endif /* DIAG_H */
