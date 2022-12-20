# Krmiljenje robotske roke Jetmax v jeziku C

## Robotska roka Jetmax

Hiwonder Jetmax JETSON NANO robotska roka z operacijskim sistemom ROS: https://www.hiwonder.hk/collections/jetson/products/hiwonder-jetmax-jetson-nano-robot-arm-ros-open-source-vision-recognition-program-robot

## HTTP strežnik za komunikacijo z robotsko roko

https://github.com/fsprojekti/shr-mfg-robotic-arm-http-server

## ESP32 plošča

joy-it SBC NodeMCU-ESP32 plošča: https://joy-it.net/en/products/SBC-NodeMCU-ESP32

Glavne značilnosti:
* **procesor**: Tensilica LX6 Dual-Core, 240 MHz
* **spomin**: 4 MB, SRAM: 512 kb
* **wifi**: 802.11 b/g/n, 2,4 GHz
* **bluetooth**: classic/LE
* **vmesniki**: UART, I2C, SPI, DAC, ADC
* **delovna napetost**: 3,3 V (5 V microUSB)

Priročnik: https://joy-it.net/files/files/Produkte/SBC-NodeMCU-ESP32/SBC-NodeMCU-ESP32-Manual-2021-06-29.pdf

## Razvojno okolje Arduino

Arduino IDE: https://www.arduino.cc/en/software

Zahtevane namestitve:
* ESP32 board
	* dodaj https://dl.espressif.com/dl/package_esp32_index.json na seznam Additional Boards Manager URLs v nastavitvah Arduino IDE (Preferences)
	* v Tools &rarr; Board izberi ESP32 Arduino &rarr; ESP32 Dev Module
* knjižnica **WiFi** (za komunikacijo med osebnim računalnikom in robotsko roko)
* knjižnica **ESPmDNS** (za podporo DNS zahtevtkom na ESP čipu)
* knjižnica **WebServer** (če želimo lokalni strežnik za dohodne HTTP zahtevke)
* knjižnica **HTTPClient** (za pošiljanje izhodnih HTTP sporočil)
* knjižnica **ArduinoJson** library (za oblikovanje HTTP sporočil v JSON formatu)

### Povezava na WiFi omrežje:
* nastavitev imena omrežja in gesla za dostop (izven setup in loop funkcij):
```
const char* ssid     = "IME OMREŽJA";
const char* password = "GESLO";
```
* vzpostavitev povezave (v setup funkciji):
```
WiFi.begin(ssid, password);
while (WiFi.status() != WL_CONNECTED) {
	delay(500);
	Serial.print(".");
}
Serial.println(WiFi.localIP());  // dodeljeni IP naslov v WiFi omrežju
```

### Pošiljanje HTTP zahtevkov na robotsko roko:
* ustvarjanje HTTP klienta: 
```
HTTPClient http;
```
* ustvarjanje HTTP sporočila: 
```
http.begin(roboticArmHttpApiIp, roboticArmHttpApiPort, "/");
```
* pošiljanje HTTP sporočila:
```
int httpCode = http.GET();
```
* preverjanje odgovora (v primeru napake je HTTP koda negativna):
```
if (httpCode > 0) {
// HTTP header has been send and Server response header has been handled
    Serial.println("HTTP response code: " + String(httpCode));
	Serial.println("HTTP response: " + http.getString());
}
// error sending HTTP request, print error messasge
else {
	Serial.println("HTTP response code: " + String(httpCode));
	Serial.println("HTTP GET failed, error:");
	Serial.println(http.errorToString(httpCode).c_str());
}
```

### Vzpostavitev lokalnega strežnika

* ustvarjanje strežnika (izven setup in loop funkcij)
```
WebServer server(8000); // 8000 je port, na katerem bo tekel strežnik
```

* nastavitev API endpointov (v setup funkciji)
```
 server.on("/", handleRoot); // za vsak endpoint se nastavi, katera funkcija naj se izvede, ko klient dostopa do endpointa
 server.onNotFound(handleNotFound); // funkcija, ki se izvede, če klient želi dostopati do endpointa, ki ni definiran
```

* definicija funkcij za upravljanje (izven setup in loop funkcij)
```
void handleRoot() {
  Serial.println("received a request to /");
  server.send(200, "text/plain", "Hello from ESP32 board");
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
```
* zagon strežnika (v setup funkciji)
```
server.begin();
```

## Naloge za študente

### stanje robotske roke
* ugotovitev lokacije robotske roke (x,y,z), stanja servo motorjev in robotskih sklepov, PWM signalov in aktivnost sesanja
### Premiki robotske roke
* premik po x/y/z osi na določeno lokacijo (absolutni premik)
* premik po x/y/z osi za določeno razdaljo (relativni premik)
### Kamera
* zajem slike s kamere
* določitev oddaljenosti predmeta (nameščen AprilTag)
### Premik predmetov
* vklop hidravličnega sesanja
* premik predmeta na drugo lokacijo
### kombinirane naloge
* premik predmeta:
	* pridobite stanja roke (lokacija)
	* premik po xy ravnini relativno od trenutne do končne lokacije
	* premik po z osi nad predmet
	* slikanje predmeta 
	* določitev oddaljenosti in izračun potrebnega premika navzdol točno do predmeta
	* vklop sesanja
	* premik po z osi gor
	* premik po xy ravnini relativno od trenutne do končne lokacije
	* premik po z osi navzdol do končne višine