#include <testLibrary.h>

Node node = Node();
 int in1, in2, in3, in4;

void setup() {
  node.initDigitalInput("I1");
  node.initDigitalInput("I6");
  node.initDigitalInput("I3");
  node.initDigitalInput("I4");
  node.initDigitalOutput("O1");
  node.initDigitalOutput("O2");
  node.initDigitalOutput("O3");
  node.initDigitalOutput("O4");
  Serial.begin(9600);
}

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
  return node.readDigitalPort("I6");
}

int readMachineHighSensor(){
  return node.readDigitalPort("I3");
}

int readMachineLowSensor(){
  return node.readDigitalPort("I4");
}

void loop() {
   stopPunching();
  stopConveyor();
  
  while(readEntrySensor() != LOW){  //WAIT for a product in the starting position
    delay(100);
  }
  Serial.write("Produto Recebido\n");
  moveConveyorFront();
  while(readWorkStationSensor() != LOW){  //WAIT for a product in the Punching station
    delay(100);
  }
  stopConveyor();
  Serial.write("Produto Na estação\n");
  
  while(readMachineLowSensor() != HIGH){
    movePunchingDown();
  }
  
  stopPunching();
  
  while(readMachineHighSensor() != HIGH){
    movePunchingUp();
  }
  
  Serial.write("Produto Acabado\n");
  stopPunching();
  
  while(readEntrySensor() != LOW){  //WAIT for a product in the starting position
    moveConveyorBack();
  }
  stopConveyor();
  delay(5000);
}
