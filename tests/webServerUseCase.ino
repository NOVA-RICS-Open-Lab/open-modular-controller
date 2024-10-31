#include <WiFi.h>
#include <AsyncTCP.h>
#include <ESPAsyncWebServer.h>
#include "protoboardLib.h"
#include "useCaseKitLib.h"

// Replace with your network credentials
const char* ssid = "YOUR-SSID";
const char* password = "YOUR-PASSWORD";

const char* PARAM_INPUT_1 = "output";
const char* PARAM_INPUT_2 = "state";
const char* STATE = "OFF";

Node node = Node();
int in1, in2, in3, in4;

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

// Create AsyncWebServer object on port 80
AsyncWebServer server(80);

const char index_html[] PROGMEM = R"rawliteral(
<!DOCTYPE HTML><html>
<head>
  <title>ESP Web Server</title>
  <meta name="viewport" content="width=device-width, initial-scale=1">
  <link rel="icon" href="data:,">
  <style>
    html {font-family: Arial; display: inline-block; text-align: center;}
    h2 {font-size: 3.0rem;}
    p {font-size: 3.0rem;}
    body {max-width: 600px; margin:0px auto; padding-bottom: 25px;}
    .switch {position: relative; display: inline-block; width: 120px; height: 68px} 
    .switch input {display: none}
    .slider {position: absolute; top: 0; left: 0; right: 0; bottom: 0; background-color: #ccc; border-radius: 6px}
    .slider:before {position: absolute; content: ""; height: 52px; width: 52px; left: 8px; bottom: 8px; background-color: #fff; -webkit-transition: .4s; transition: .4s; border-radius: 3px}
    input:checked+.slider {background-color: #b30000}
    input:checked+.slider:before {-webkit-transform: translateX(52px); -ms-transform: translateX(52px); transform: translateX(52px)}
    .center-image {
      display: flex;
      justify-content: center;
      align-items: center;
    }
  </style>
</head>
<body>
  <h2>ESP Web Server</h2>
  %BUTTONPLACEHOLDER%
<script>function toggleCheckbox(element) {
  var xhr = new XMLHttpRequest();
  if(element.checked){ xhr.open("GET", "/update?output="+element.id+"&state=1", true); }
  else { xhr.open("GET", "/update?output="+element.id+"&state=0", true); }
  xhr.send();
}
</script>
</body>
<body2>
    <div class="center-image">
      <a data-flickr-embed="true" href="https://www.flickr.com/photos/199239236@N04/53217524602/in/dateposted-public/" title="kit">
        <img src="https://live.staticflickr.com/65535/53217524602_f9231e8afb.jpg" width="500" height="364" alt="kit"/>//</a>
      <script async src="//embedr.flickr.com/assets/client-code.js" charset="utf-8"></script>
    </div>
</body2>
<index>
    <div class="center-image">
      <img src="https://upload.wikimedia.org/wikipedia/commons/c/ca/Novologofct2021.png" alt="Novologofct2021.png" width="200" height="146">
      <img src="https://www.uninova.pt/sites/default/files/styles/logotipo/public/logo/logotipo_uninova_0.png?itok=XI5qW0Kv" alt="UNINOVA.png" width="200" height="60">
      <img src="https://static.wixstatic.com/media/56223c_983be1e886664ecebd19a66e1ab5e14b~mv2.png/v1/fill/w_190,h_99,al_c,q_85,usm_0.66_1.00_0.01,enc_auto/rics_image_red.png" alt="RICSLOGO.png" width="200" height="100">          
    </div>
</index>
</html>
)rawliteral";


String outputState(){
  if(STATE == "ON"){
    return "checked";
  }
  else {
    return "";
  }
}


// Replaces placeholder with button section in your web page
String processor(const String& var){
  //Serial.println(var);
  if(var == "BUTTONPLACEHOLDER"){
    String buttons = "";
    buttons += "<h4>Output - IndustrialKit</h4><label class=\"switch\"><input type=\"checkbox\" onchange=\"toggleCheckbox(this)\" id=\"2\" " + outputState() + "><span class=\"slider\"></span></label>";
    return buttons;
  }
  return String();
}


void setup(){
  // Serial port for debugging purposes
  Serial.begin(115200);

  node.initDigitalInput("I1");
  node.initDigitalInput("I2");
  node.initDigitalInput("I3");
  node.initDigitalInput("I4");
  node.initDigitalOutput("O1");
  node.initDigitalOutput("O2");
  node.initDigitalOutput("O3");
  node.initDigitalOutput("O4");

  // Connect to Wi-Fi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi..");
  }

  // Print ESP Local IP Address
  Serial.println(WiFi.localIP());

  // Route for root / web page
  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send_P(200, "text/html", index_html, processor);
  });

  // Send a GET request to <ESP_IP>/update?output=<inputMessage1>&state=<inputMessage2>
  server.on("/update", HTTP_GET, [] (AsyncWebServerRequest *request) {
    String inputMessage1;
    String inputMessage2;

    // GET input1 value on <ESP_IP>/update?output=<inputMessage1>&state=<inputMessage2>
    if (request->hasParam(PARAM_INPUT_1) && request->hasParam(PARAM_INPUT_2)) {
      inputMessage1 = request->getParam(PARAM_INPUT_1)->value();
      inputMessage2 = request->getParam(PARAM_INPUT_2)->value();

      if(inputMessage2.toInt()==1){
        STATE="ON";
      }

      else{
        STATE="OFF";
      }

    }

    else {
      inputMessage1 = "No message sent";
      inputMessage2 = "No message sent";
    }

    Serial.print("MACHINE: ");
    Serial.print(inputMessage1);
    Serial.print(" - Set to: ");
    Serial.println(inputMessage2);
    request->send(200, "text/plain", "OK");
  });

  // Start server
  server.begin();
}


void loop() {
  machineExecution();
}
