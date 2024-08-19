#include "EEPROM.h"
#include <SPI.h>
#include "messageHandlers.h"
#include "communication.h"

// Mensajes que se reciben
const String MESSAGE_ISCONNECT = "IsConnect";

// Mensajes que se envian
const String MESSAGE_RELEASED = "Released";
const String MESSAGE_CHANGE = "Change";

void handleUnknownMessage()
{
    Serial.println("Mensaje no reconocido");
}

// Enviar mensaje para la liberacion
void handleReleasedMessage()
{
    transmitir(MESSAGE_RELEASED);
}

// Enviar mensaje para el pulso
void handleChangeMessage()
{
    transmitir(MESSAGE_CHANGE);
}

// Manejador de nueva conexión
void handleConnectMessage() {
    Serial.println("Mensaje enviado: IsConnect");
}
