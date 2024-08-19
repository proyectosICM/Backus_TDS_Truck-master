#ifndef RANGING_H
#define RANGING_H

#include <SPI.h>
#include "DW1000Ranging.h"
#include "DW1000.h"

// Definición de pines
#define SPI_SCK    12
#define SPI_MISO   13
#define SPI_MOSI   11
#define DW_CS      10
#define PIN_RST    8
#define PIN_IRQ    6
#define PIN_SS     10

// Dirección MAC del tag
extern char tag_addr[];

// Distancia límite en metros
extern float distanceThreshold;

// Variable para almacenar la dirección del anchor actual
extern uint16_t currentAnchorAddr;

void setupSPI();
void setupDW1000();
void newRange();
void newDevice(DW1000Device *device);
void inactiveDevice(DW1000Device *device);

#endif
