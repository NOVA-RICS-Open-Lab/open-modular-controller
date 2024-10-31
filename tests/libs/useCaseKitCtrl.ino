#include "protoboardLib.h"

Node node = Node();
int in1, in2, in3, in4;

void stopConveyor(){
  node.writeDigitalPort("O1",LOW);
  node.writeDigitalPort("O2",LOW);
  return;
}


void moveConveyorFront(){
  node.writeDigitalPort("O1",HIGH);
  node.writeDigitalPort("O2",LOW);
  return;
}


void moveConveyorBack(){
  node.writeDigitalPort("O1",LOW);
  node.writeDigitalPort("O2",HIGH);
  return;
}

void movePunchingUp(){
  node.writeDigitalPort("O3",HIGH);
  node.writeDigitalPort("O4",LOW);
  return;
}


void movePunchingDown(){
  node.writeDigitalPort("O3",LOW);
  node.writeDigitalPort("O4",HIGH);
  return;
}


void stopPunching(){
  node.writeDigitalPort("O3",LOW);
  node.writeDigitalPort("O4",LOW);
  return;
}


int readEntrySensor(){
  return node.readDigitalPort("I1");
}


int readWorkStationSensor(){
  return node.readDigitalPort("I2");
}


int readMachineHighSensor(){
  return node.readDigitalPort("I3");
}


int readMachineLowSensor(){
  return node.readDigitalPort("I4");
}
