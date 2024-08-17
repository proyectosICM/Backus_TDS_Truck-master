#ifndef MESH_MANAGER_H
#define MESH_MANAGER_H

#include <painlessMesh.h>
#include <EEPROM.h>
#include "config.h"

// Declaraciones de funciones
void newConnectionCallback(uint32_t nodeId);
void nodeTimeAdjustedCallback(int32_t offset);
void changedConnectionCallback();
void setUpMesh();
void updateCredentials(uint16_t port_selected);
bool sendMessage(String msg);


void handleLongPress();
void handleButtonRelease();
void updateButtonState(int buttonState);

void readButtonState();
void readButtonState2();

// Declaraciones de variables globales
extern painlessMesh mesh;
extern char mesh_prefix[10];
extern char mesh_password[12];
extern uint16_t mesh_port;
extern uint16_t mesh_port_num;
extern bool pressed_long;
extern uint8_t flagStateMachine;
extern unsigned long minButtonLongPressDuration;
extern unsigned long buttonLongPressMillis;
extern bool buttonStateLongPress;
extern const int intervalButton;
extern unsigned long previousButtonMillis;
extern unsigned long buttonPressDuration;
extern unsigned long currentMillis;

#endif // MESH_MANAGER_H
