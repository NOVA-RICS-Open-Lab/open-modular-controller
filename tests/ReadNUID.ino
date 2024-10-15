#include <SPI.h>
#include <MFRC522.h>
#include <testLibrary.h>

#define SS_PIN 15
#define RST_PIN 23
 
MFRC522 rfid(SS_PIN); // Instance of the class
MFRC522::MIFARE_Key key;

String KeyRing = "EA8BF180";
String   Card1 = "917C444C";
String   Card2 = "84143474";
String   Card3 = "81FD494C";
String   Card4 = "50D7B711";
String   tagID = "";

int Pressings = 1;

Node node = Node();

// Init array that will store new NUID 
byte nuidPICC[4];

//Functions for Kit Interaction
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

//Industrial Kit Movement Sequence
void WorkingMachine() {
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
  for(int i=0; i<Pressings; i++){
    while(readMachineLowSensor() != HIGH){
      movePunchingDown();
    }
    stopPunching();
    delay(1000);
    while(readMachineHighSensor() != HIGH){
      movePunchingUp();
    }
    stopPunching();
  }
  while(readEntrySensor() != LOW){  //WAIT for a product in the starting position
    moveConveyorBack();
  }
  stopConveyor();
  Serial.write("Produto Acabado\n");
}

//Read new tag if available
boolean getID() 
{
  // Getting ready for Reading PICCs
  if ( ! rfid.PICC_IsNewCardPresent()) { //If a new PICC placed to RFID reader continue
  return false;
  }
  if ( ! rfid.PICC_ReadCardSerial()) { //Since a PICC placed get Serial and continue
  return false;
  }
  tagID = "";
  for ( uint8_t i = 0; i < 4; i++) { // The MIFARE PICCs that we use have 4 byte UID
  //readCard[i] = mfrc522.uid.uidByte[i];
  tagID.concat(String(rfid.uid.uidByte[i], HEX)); // Adds the 4 bytes in a single String variable
  }
  tagID.toUpperCase();
  rfid.PICC_HaltA(); // Stop reading
  return true;
}

void setup() {
  //Controller Interface initialization
  node.initDigitalInput("I1");
  node.initDigitalInput("I2");
  node.initDigitalInput("I3");
  node.initDigitalInput("I4");
  node.initDigitalOutput("O1");
  node.initDigitalOutput("O2");
  node.initDigitalOutput("O3");
  node.initDigitalOutput("O4");

  Serial.begin(9600);
  SPI.begin(14, 12, 13, 4);      // Init SPI bus
  rfid.PCD_Init(); // Init MFRC522 

  for (byte i = 0; i < 6; i++) {
    key.keyByte[i] = 0xFF;
  }

  Serial.println(F("Ready to read RFID card"));
}
 
void loop() {
  
  //Wait until new tag is available
  while (getID()) {
    if (tagID == KeyRing){
      Serial.println("Product1 RFID read");
      Pressings = 1;
    }
    if (tagID == Card1){
      Serial.println("Product2 RFID read");
      Pressings = 2;
    }
    if (tagID == Card2){
      Serial.println("Product3 RFID read");
      Pressings = 3;
    }
    if (tagID == Card3){
      Serial.println("Product4 RFID read");
      Pressings = 4;
    }
    if (tagID == Card4){
      Serial.println("Product5 RFID read");
      Pressings = 5;
    }
  }
  WorkingMachine();
  Serial.println(F("Ready to read RFID card"));
  }
