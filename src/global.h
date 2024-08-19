#ifndef GLOBAL_H
#define GLOBAL_H

#include <Arduino.h>
#include "painlessMesh.h"
#include "EEPROM.h"

// Scheduler for controlling personal tasks
extern Scheduler userScheduler;
extern painlessMesh mesh;

// Variables para envio y recepcion de mensajes
extern volatile boolean received;
extern String message;

// Variables y constantes relacionadas con el botón
extern int buttonStatePrevious;
extern unsigned long minButtonLongPressDuration;
extern unsigned long buttonLongPressMillis;
extern bool buttonStateLongPress;
extern const int intervalButton;
extern unsigned long previousButtonMillis;
extern unsigned long buttonPressDuration;
extern unsigned long currentMillis;

#endif 
 