#ifndef COMMUNICATION_H
#define COMMUNICATION_H

#include <Arduino.h>
#include "config.h"
#include "painlessMesh.h"


void setupCommunication();
bool sendMessage(String msg);
void transmitir(String message);
void receiver();


void receivedCallback();

void handleReceived();

#endif
 