#include "protoboardLib.h"

Node node = Node();
int in1, in2;

void setup() {
  node.initDigitalInput("I6");
  Serial.begin(9600);
}


void loop() {
  in2 = node.readDigitalPort("I6");
  Serial.write("->");

  if(in2 == LOW){
    Serial.write("Sensor 2 not active\n");
  }

  if(in2 == HIGH){
    Serial.write("Sensor 2 is active\n");
      
  } 
  delay(5000);
}
