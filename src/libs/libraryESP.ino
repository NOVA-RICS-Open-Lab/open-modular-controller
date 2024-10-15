#include <testLibrary.h>

Node node = Node();
 int in1, in2, in3, in4;

void setup() {
  node.initDigitalInput("D8");
  node.initDigitalInput("D9");
  node.initDigitalInput("D10");
  node.initDigitalInput("D11");
  node.initDigitalOutput("D0");
  node.initDigitalOutput("D1");
  node.initDigitalOutput("D2");
  node.initDigitalOutput("D12");
  Serial.begin(9600);
}

void stopConveyor(){
    node.writeDigitalPort("D0",LOW);
    node.writeDigitalPort("D1",LOW);
    return;
}

void moveConveyorFront(){
    node.writeDigitalPort("D0",HIGH);
    node.writeDigitalPort("D1",LOW);
    return;
}

void moveConveyorBack(){
    node.writeDigitalPort("D0",LOW);
    node.writeDigitalPort("D1",HIGH);
    return;
}



void movePunchingDown(){
    node.writeDigitalPort("D2",HIGH);
    node.writeDigitalPort("D12",LOW);
    return;
}
void movePunchingUp(){
    node.writeDigitalPort("D2",LOW);
    node.writeDigitalPort("D12",HIGH);
    return;
}
void stopPunching(){
    node.writeDigitalPort("D2",LOW);
    node.writeDigitalPort("D12",LOW);
    return;
}


int readEntrySensor(){
  return node.readDigitalPort("D8");
}

int readWorkStationSensor(){
  return node.readDigitalPort("D9");
}

int readMachineHighSensor(){
  return node.readDigitalPort("D10");
}

int readMachineLowSensor(){
  return node.readDigitalPort("D11");
}

void loop() {

  stopPunching();
  stopConveyor();
  
  while(readEntrySensor() != HIGH){  //WAIT for a product in the starting position
    delay(100);
  }
  Serial.write("Produto Recebido\n");
  moveConveyorBack();
  while(readWorkStationSensor() != HIGH){  //WAIT for a product in the Punching station
    delay(100);
  }
  stopConveyor();
  Serial.write("Produto Na estação\n");
  
  while(readMachineLowSensor() != LOW){
    movePunchingDown();
  }
  
  stopPunching();
  
  while(readMachineHighSensor() != LOW){
    movePunchingUp();
  }
  
  Serial.write("Produto Acabado\n");
  stopPunching();
  
  while(readEntrySensor() != HIGH){  //WAIT for a product in the starting position
    moveConveyorFront();
  }
  stopConveyor();
  delay(10000);
}
