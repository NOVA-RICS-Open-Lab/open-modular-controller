#include <SPI.h>
#include <MFRC522.h>
#include "protoboardLib.h"
#include "useCaseKitLib.h"

#define SS_PIN 15
#define RST_PIN 23
 
MFRC522 rfid(SS_PIN);
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

// Industrial Kit Movement Sequence
void machineExecution() {
  while(STATE != "OFF"){
      
    stopPunching();
    stopConveyor();

    // WAIT for a product in the starting position
    while(readEntrySensor() != LOW){  
      delay(100);
    }

    Serial.write("Product received\n");
    moveConveyorFront();

    // WAIT for a product in the Punching station
    while(readWorkStationSensor() != LOW){  
      delay(100);
    }

    stopConveyor();
    Serial.write("Product in station\n");

    // EXECUTE Punching routine
    while(readMachineLowSensor() != HIGH){
      movePunchingDown();
    }

    stopPunching();
    delay(1500);

    while(readMachineHighSensor() != HIGH){
      movePunchingUp();
    }

    stopPunching();

    // WAIT for a product in the starting position
    while(readEntrySensor() != LOW){  
      moveConveyorBack();
    }

    stopConveyor();
    Serial.write("Process finished\n");

  }
  return;
}


//Read new tag if available
boolean getID() {
  // Getting ready for Reading PICCs
  if ( ! rfid.PICC_IsNewCardPresent()) { 
    // If a new PICC placed to RFID reader continue
    return false;
  }

  if ( ! rfid.PICC_ReadCardSerial()) { 
    // Since a PICC placed get Serial and continue
    return false;
  }

  tagID = "";

  for ( uint8_t i = 0; i < 4; i++) { 
    // The MIFARE PICCs that we use have 4 byte UID
    // readCard[i] = mfrc522.uid.uidByte[i];

    // Adds the 4 bytes in a single String variable
    tagID.concat(String(rfid.uid.uidByte[i], HEX)); 
  }

  tagID.toUpperCase();
  // Stop reading
  rfid.PICC_HaltA();

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
  // Init SPI bus
  SPI.begin(14, 12, 13, 4);
  // Init MFRC522 
  rfid.PCD_Init(); 

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

  machineExecution();

  Serial.println(F("Ready to read RFID card"));
}
