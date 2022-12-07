#include <WiFi.h>;
#include <WebServer.h>
#include <ESPmDNS.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>


// **************** global app variables *********************
int state = 1; // default: 1
bool busy = false; // default: false
// this flag is set to true in the first iteration of the loop after busy variable is set to true and set to false immediately after that
bool startFlag = false;

// **************** WiFi parameters *********************
const char* ssid     = "DESKTOP-4NT77NL-4917";
const char* password = "TPlaptopHOTSPOT";

// const char* ssid     = "TP-LINK_0B69";
// const char* password = "29205820";

WebServer server(8000);

String roboticArmHttpApiIp = "192.168.137.1";
int roboticArmHttpApiPort = 3000;

// create HTTP client
HTTPClient http;

// **************** web server handles *********************
void handleRoot() {

  Serial.println("received a request to /");
  server.send(200, "text/plain", "Hello from DF micro:Maqueen Plus!");
}

void handleNotFound() {
  String message = "File Not Found\n\n";
  message += "URI: ";
  message += server.uri();
  message += "\nMethod: ";
  message += (server.method() == HTTP_GET) ? "GET" : "POST";
  message += "\nArguments: ";
  message += server.args();
  message += "\n";
  for (uint8_t i = 0; i < server.args(); i++) {
    message += " " + server.argName(i) + ": " + server.arg(i) + "\n";
  }
  server.send(404, "text/plain", message);
}

void setup() {
  // initialize serial print
  Serial.begin(115200);

  // connect to a WiFi network
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  Serial.println("");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected.");
  Serial.println("IP address: ");

  Serial.println(WiFi.localIP());
  Serial.println("MAC address: ");
  Serial.println(WiFi.macAddress());

  // start the local server (for incoming requests to the robot car)
  if (MDNS.begin("esp32")) {
    Serial.println("MDNS responder started");
  }

  // web server API endpoints
  server.on("/", handleRoot);
  server.onNotFound(handleNotFound);

  // start web server
  server.begin();
  Serial.println("HTTP server started");

}

void loop() {

  // handle incoming requests
  server.handleClient();

  // create HTTP client
  HTTPClient http;

  // Serial.println("robot state: " + String(state));


  // car robot driving algorithm
  switch (state) {
    // default case, the car is free (busy = false) and waits for the next request to move
    case 1: {
        // Serial.println("case 1 ...");
        String httpURL = roboticArmHttpApiIp + ":" + String(roboticArmHttpApiPort) + "/";
        Serial.println("http url: " + httpURL);
        http.begin(roboticArmHttpApiIp, roboticArmHttpApiPort, "/"); //HTTP
        // start the connection and send HTTP header
        int httpCode = http.GET();

        // httpCode will be negative on error
        if (httpCode > 0) {
          // HTTP header has been send and Server response header has been handled
          Serial.println("HTTP response code: " + String(httpCode));
          Serial.println("HTTP response: " + http.getString());

          state = 2;
        }
        // error sending HTTP request to the Node.js control app, retry
        else {
          Serial.println("HTTP response code: " + String(httpCode));
          Serial.println("HTTP GET failed, error:");
          Serial.println(http.errorToString(httpCode).c_str());
        }
        break;
      }
    case 2: {
        // Serial.println("case 2 ...");
        String httpURL = roboticArmHttpApiIp + ":" + String(roboticArmHttpApiPort) + "/basic/moveTo";
        Serial.println("HTTP url: " + httpURL);
        http.begin(roboticArmHttpApiIp, roboticArmHttpApiPort, "/basic/moveTo"); //HTTP
        // start the connection and send HTTP header
        int httpCode = http.GET();

        // httpCode will be negative on error
        if (httpCode > 0) {
          // HTTP header has been send and Server response header has been handled
          Serial.println("HTTP response code: " + String(httpCode));
          Serial.println("HTTP response: " + http.getString());

          state = 3;
        }
        // error sending HTTP request to the Node.js control app, retry
        else {
          Serial.println("HTTP response code: " + String(httpCode));
          Serial.println("HTTP GET failed, error:");
          Serial.println(http.errorToString(httpCode).c_str());
        }
        break;
      }
    case 3: {
        // Serial.println("case 3 ...");
        String httpURL = roboticArmHttpApiIp + ":" + String(roboticArmHttpApiPort) + "/basic/move";
        Serial.println("HTTP url: " + httpURL);
        http.begin(roboticArmHttpApiIp, roboticArmHttpApiPort, "/basic/move"); //HTTP
        // start the connection and send HTTP header
        int httpCode = http.GET();

        // httpCode will be negative on error
        if (httpCode > 0) {
          // HTTP header has been send and Server response header has been handled
          Serial.println("HTTP response code: " + String(httpCode));
          Serial.println("HTTP response: " + http.getString());

          state = 4;
          delay(2000);
        }
        // error sending HTTP request to the Node.js control app, retry
        else {
          Serial.println("HTTP response code: " + String(httpCode));
          Serial.println("HTTP GET failed, error:");
          Serial.println(http.errorToString(httpCode).c_str());
        }
        break;
      }
    case 4: {
        // Serial.println("case 4 ...");
        String httpURL = roboticArmHttpApiIp + ":" + String(roboticArmHttpApiPort) + "/basic/suction";
        Serial.println("HTTP url: " + httpURL);
        http.begin(roboticArmHttpApiIp, roboticArmHttpApiPort, "/basic/suction"); //HTTP
        // start the connection and send HTTP header
        int httpCode = http.GET();

        // httpCode will be negative on error
        if (httpCode > 0) {
          // HTTP header has been send and Server response header has been handled
          Serial.println("HTTP response code: " + String(httpCode));
          Serial.println("HTTP response: " + http.getString());

          state = 1;

        }
        // error sending HTTP request to the Node.js control app, retry
        else {
          Serial.println("HTTP response code: " + String(httpCode));
          Serial.println("HTTP GET failed, error:");
          Serial.println(http.errorToString(httpCode).c_str());
        }
        break;
      }
  }
}
