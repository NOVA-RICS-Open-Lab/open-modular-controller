#ifndef useCaseKitLib_h
#define useCaseKitLib_h

#include "Arduino.h"

// DIGITAL OUTPUT
void stopConveyor();
void moveConveyorFront();
void moveConveyorBack();
void movePunchingUp();
void movePunchingDown();
void stopPunching();

// DIGITAL INPUT
int readEntrySensor();
int readWorkStationSensor();
int readMachineHighSensor();
int readMachineLowSensor();

#endif
