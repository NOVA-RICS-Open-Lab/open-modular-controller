#include <WiFi.h>
#include <testLibrary.h>

// Replace with your network credentials
const char* ssid = "RICS-PUB";
const char* password = "ricsricsjabjab";

// Set web server port number to 80
WiFiServer server(80);

// Variable to store the HTTP request
String header;

// Auxiliar variables to store the current output state
String machineState = "off";

// Assign output variables to GPIO pins
Node node = Node();
int in1, in2, in3, in4;

// Current time
unsigned long currentTime = millis();
// Previous time
unsigned long previousTime = 0; 
// Define timeout time in milliseconds (example: 2000ms = 2s)
const long timeoutTime = 2000;

//Functions for Kit Actuating 
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
  while(readMachineLowSensor() != HIGH){
    movePunchingDown();
  }
  stopPunching();
  while(readMachineHighSensor() != HIGH){
    movePunchingUp();
  }
  stopPunching();
  while(readEntrySensor() != LOW){  //WAIT for a product in the starting position
    moveConveyorBack();
  }
  stopConveyor();
  Serial.write("Produto Acabado\n");
  machineState="idle";
}

void setup() {
  
  node.initDigitalInput("I1");
  node.initDigitalInput("I6");
  node.initDigitalInput("I3");
  node.initDigitalInput("I4");
  node.initDigitalOutput("O1");
  node.initDigitalOutput("O2");
  node.initDigitalOutput("O3");
  node.initDigitalOutput("O4");
 
  Serial.begin(115200);

  // Connect to Wi-Fi network with SSID and password
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  // Print local IP address and start web server
  Serial.println("");
  Serial.println("WiFi connected.");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
  server.begin();
}

void loop(){
  WiFiClient client = server.available();   // Listen for incoming clients
  if(readMachineHighSensor() == HIGH){
    machineState="idle";
  }
  
  if (client) {                             // If a new client connects,
    currentTime = millis();
    previousTime = currentTime;
    Serial.println("New Client.");          // print a message out in the serial port
    String currentLine = "";                // make a String to hold incoming data from the client
    while (client.connected() && currentTime - previousTime <= timeoutTime) {  // loop while the client's connected
      currentTime = millis();
      if (client.available()) {             // if there's bytes to read from the client,
        char c = client.read();             // read a byte, then
        Serial.write(c);                    // print it out the serial monitor
        header += c;
        if (c == '\n') {                    // if the byte is a newline character
          // if the current line is blank, you got two newline characters in a row.
          // that's the end of the client HTTP request, so send a response:
          if (currentLine.length() == 0) {
            // HTTP headers always start with a response code (e.g. HTTP/1.1 200 OK)
            // and a content-type so the client knows what's coming, then a blank line:
            client.println("HTTP/1.1 200 OK");
            client.println("Content-type:text/html");
            client.println("Connection: close");
            client.println();
            
            // turns the GPIOs on and off
            if (header.indexOf("GET /machine/on") >= 0) {
              Serial.println("Industrial Kit Working");
              machineState = "working";
              WorkingMachine();
            }
            
            // Display the HTML web page
            client.println("<!DOCTYPE html><html>");
            client.println("<head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">");
            client.println("<link rel=\"icon\" href=\"data:,\">");
            // CSS to style the on/off buttons 
            // Feel free to change the background-color and font-size attributes to fit your preferences
            client.println("<style>html { font-family: Helvetica; display: inline-block; margin: 0px auto; text-align: center;}");
            client.println(".button { background-color: #4CAF50; border: none; color: white; padding: 16px 40px;");
            client.println("text-decoration: none; font-size: 30px; margin: 2px; cursor: pointer;}");
            client.println(".button2 {background-color: #555555;}");
            client.println("text-decoration: none; font-size: 30px; margin: 2px; cursor: pointer;}");
            client.println(".button3 {background-color: #FF0000;}</style></head>");
            
            // Web Page Heading
            client.println("<body><h1>Controller Web Server</h1>");
            
            // Display current state, and ON/OFF buttons for Machine  
            // If the machineState is idle, it displays the ON button       
            if (machineState=="idle") {
              client.println("<p><a href=\"/machine/on\"><button class=\"button\">Activate</button></a></p>");
            } else if(machineState=="working"){
              client.println("<p><a href=\"\"><button class=\"button button2\">Working</button></a></p>");
            } else if(machineState=="off"){
              client.println("<p><a href=\"\"><button class=\"button button3\">OFF</button></a></p>");
            } 
            client.println("</body></html>");
            
            // The HTTP response ends with another blank line
            client.println();
            // Break out of the while loop
            break;
          } else { // if you got a newline, then clear currentLine
            currentLine = "";
          }
        } else if (c != '\r') {  // if you got anything else but a carriage return character,
          currentLine += c;      // add it to the end of the currentLine
        }
      }
    }
    // Clear the header variable
    header = "";
    // Close the connection
    client.stop();
    Serial.println("Client disconnected.");
    Serial.println("");
  }
}
