#include "meshManager.h"
#include <EEPROM.h>
#include "uwb.h"
#include "eepromManager.h"

// Definiciones de variables globales
Scheduler userScheduler;
painlessMesh mesh;


bool pressed_long = false;
#define EEPROM_SIZE 96

char closerDeviceName[20] = "";
int16_t leastRssi = -255;
uint8_t flagStateMachine = 0;
char mesh_prefix[10] = "HANGAR";
char mesh_password[12] = "project2024";
uint16_t mesh_port = 5550;
uint16_t mesh_port_num;

int buttonStatePrevious = HIGH;
unsigned long minButtonLongPressDuration = 2000;
unsigned long buttonLongPressMillis;
bool buttonStateLongPress = false;
const int intervalButton = 50;
unsigned long previousButtonMillis;
unsigned long buttonPressDuration;
unsigned long currentMillis;

void newConnectionCallback(uint32_t nodeId) {
  Serial.printf("--> startHere: New Connection, nodeId = %u\n", nodeId);
  digitalWrite(RED, LOW);
  digitalWrite(LED, HIGH);
}

void nodeTimeAdjustedCallback(int32_t offset) {
  Serial.printf("Adjusted time %u Offset = %d\n", mesh.getNodeTime(), offset);
}

void changedConnectionCallback() {
  Serial.printf("Changed connections\n");
  if (flagStateMachine == 1 && pressed_long) {
    digitalWrite(RED, HIGH);
    digitalWrite(LED, LOW);
    flagStateMachine = 2;
  }
}

void setUpMesh() {
  Serial.println("Starting WiFi Mesh");
  mesh.setDebugMsgTypes(ERROR | STARTUP);
  mesh.init(mesh_prefix, mesh_password, &userScheduler, mesh_port);
  mesh.onChangedConnections(&changedConnectionCallback);
  mesh.onNewConnection(&newConnectionCallback);
  mesh.onNodeTimeAdjusted(&nodeTimeAdjustedCallback);
  save2EEPROM(mesh_port, mesh_prefix);
}

void updateCredentials(uint16_t port_selected) {
  sprintf(mesh_prefix, "HANGAR%i", port_selected);
  mesh_port = 5550 + port_selected;
}

bool sendMessage(String msg) {
  return mesh.sendBroadcast(msg);
}

void readButtonState() {
  if (currentMillis - previousButtonMillis > intervalButton) {
    int buttonState = digitalRead(MAIN_BUTTON);

    if (buttonState == LOW && buttonStatePrevious == HIGH && !buttonStateLongPress) {
      buttonLongPressMillis = currentMillis;
      buttonStatePrevious = LOW;
      Serial.println("Button pressed");
    }

    buttonPressDuration = currentMillis - buttonLongPressMillis;

    if (buttonState == LOW && !buttonStateLongPress && buttonPressDuration >= minButtonLongPressDuration) {
      buttonStateLongPress = true;
      Serial.println("Button long pressed");
      if (flagStateMachine == 1) {
        if (!sendMessage("Released")) {
          Serial.println("ERROR...");
          flagStateMachine = 2;
          digitalWrite(LED, LOW);
          digitalWrite(RED, HIGH);
        } else {
          pressed_long = true;
        }
      } else if (flagStateMachine == 0) {
        pressed_long = false;
      }
    }

    if (buttonState == HIGH && buttonStatePrevious == LOW) {
      buttonStatePrevious = HIGH;
      buttonStateLongPress = false;
      if (buttonPressDuration < minButtonLongPressDuration) {
        Serial.println("Button pressed shortly");
        if (flagStateMachine == 0) {
          if (mesh_port_num != 0) {
            digitalWrite(RED, LOW);
            setUpMesh();
            flagStateMachine = 1;
          }
        } else if (flagStateMachine == 1) {
          if (range_from_selection >= 5) {
            if (!sendMessage("Change")) {
              Serial.println("ERROR...");
            }
          }
        }
      }
      Serial.println("Button released");
    }
    previousButtonMillis = currentMillis;
  }
}
