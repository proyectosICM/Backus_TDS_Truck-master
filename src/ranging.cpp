#include "ranging.h"
#include "config.h"

char tag_addr[] = "7D:00:22:EA:82:60:3B:9C";
float distanceThreshold = 2.0;
uint16_t currentAnchorAddr = 0;

void setupSPI()
{
    SPI.begin(SPI_SCK, SPI_MISO, SPI_MOSI);
}

void setupDW1000()
{
    DW1000Ranging.initCommunication(PIN_RST, PIN_SS, PIN_IRQ);
    DW1000Ranging.attachNewRange(newRange);
    DW1000Ranging.attachNewDevice(newDevice);
    DW1000Ranging.attachInactiveDevice(inactiveDevice);
    DW1000Ranging.startAsTag(tag_addr, DW1000.MODE_LONGDATA_RANGE_LOWPOWER, false);
}

void newRange()
{
    DW1000Device *device = DW1000Ranging.getDistantDevice();
    if (device)
    {
        uint16_t deviceAddr = device->getShortAddress();
        if (deviceAddr == currentAnchorAddr)
        {
            float distance = device->getRange();
            Serial.print("Anchor ");
            Serial.print(deviceAddr, HEX);
            Serial.print(", Distance: ");
            Serial.println(distance);
            // Control del LED según la distancia
            if (distance <= distanceThreshold)
            {
                digitalWrite(LED_RED, HIGH);
                Serial.println("LED encendido");
            }
            else
            { 
                digitalWrite(LED_RED, LOW);
                Serial.println("LED apagado");
            }
        }
    }
}

void newDevice(DW1000Device *device)
{
    Serial.print("Device added: ");
    Serial.println(device->getShortAddress(), HEX);
    if (currentAnchorAddr == 0)
    {
        currentAnchorAddr = device->getShortAddress();
        Serial.print("Connected to new Anchor: ");
        Serial.println(currentAnchorAddr, HEX);
    }
}

void inactiveDevice(DW1000Device *device)
{
    Serial.print("Delete inactive device: ");
    Serial.println(device->getShortAddress(), HEX);
    if (device->getShortAddress() == currentAnchorAddr)
    {
        Serial.println("Anchor disconnected");
        currentAnchorAddr = 0;    
        digitalWrite(LED_RED, LOW); 
    }
}
