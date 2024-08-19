#include "painlessMesh.h"
#include "EEPROM.h"
// C libaries
#include <cstring>
#include <string.h>
#include <stdio.h>  /* printf */
#include <stdlib.h> /* strtol */
#include "eepromManager.h"
#include "config.h"
#include "ranging.h"

void setup()
{
  Serial.begin(115200);
  pinMode(MAIN_BUTTON, INPUT_PULLUP);
  pinMode(LED_GREEN, OUTPUT);
  pinMode(LED_RED, OUTPUT);

  digitalWrite(LED_RED, HIGH);
  digitalWrite(LED_GREEN, LOW);
  Serial.println("\nInitialize EEPROM Library\n");
  EEPROM.begin(EEPROM_SIZE);

  // Inicializar SPI y DW1000
  setupSPI();
  setupDW1000();
}

void loop()
{
  DW1000Ranging.loop();
  //receivedCallback();
}