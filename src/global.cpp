#include "global.h"

extern Scheduler userScheduler;
extern painlessMesh mesh; 

// Inicialización de variables
int buttonStatePrevious = HIGH;
unsigned long minButtonLongPressDuration = 2000;
unsigned long buttonLongPressMillis = 0;
bool buttonStateLongPress = false;
const int intervalButton = 50;
unsigned long previousButtonMillis = 0;
unsigned long buttonPressDuration = 0;
unsigned long currentMillis = 0;