#include "painlessMesh.h"
#include "EEPROM.h"
#include "uwb.h"
// C libaries
#include <cstring>
#include <string.h>
#include <stdio.h>      /* printf */
#include <stdlib.h>     /* strtol */
#include "eepromManager.h"
#include "meshManager.h"
#include "config.h"


void setup() {
  Serial.begin(115200);
  pinMode(MAIN_BUTTON, INPUT_PULLUP);
  pinMode(LED, OUTPUT);
  pinMode(RED, OUTPUT);

  digitalWrite(RED, HIGH); //<- descomentar
  digitalWrite(LED, LOW);
  Serial.println("\nInitialize EEPROM Library\n");
  EEPROM.begin(EEPROM_SIZE);

  init_UWB();
  // Leer datos de la EEPROM
  //readCredentials();
}

void loop(){
  // ------------------ TOP SLOT ----------------
  uwb_main(flagStateMachine);
  currentMillis = millis();
  readButtonState();
  // ---------------- Fin TOP SLOT --------------
  switch(flagStateMachine){
    case 0:
      updateCredentials(mesh_port_num);
      //Serial.printf("El más cercano es", mesh_port_num);
      break;
    case 1:
      mesh.update();
      break;
    case 2:
      mesh.stop();
      delay(5000);
      pressed_long = false;
      flagStateMachine = 0;
      Serial.println("Starting again at flag = 0");
      break;
    default:
      //mesh.update();
      //flagStateMachine = 2;
      break;
  }
  //---------------- BOTTOM SLOT--------------
  //-------------- Fin BOTTOM SLOT------------
}