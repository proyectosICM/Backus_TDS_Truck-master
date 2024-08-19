#ifndef MESSAGE_HANDLERS_H
#define MESSAGE_HANDLERS_H

#include <Arduino.h>

// Mensajes que se reciben
extern const String MESSAGE_ISCONNECT;

//Mensajes que se envian
extern const String MESSAGE_RELEASED;
extern const String MESSAGE_CHANGE;

// Declaración de funciones handler
//void handleConnectMessage();
void handleChangeMessage();
void handleReleasedMessage();
void handleUnknownMessage();



#endif
