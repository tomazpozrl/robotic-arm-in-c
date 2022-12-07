# Krmiljenje robotske roke Jetmax v jeziku C

## Robotska roka Jetmax

Hiwonder Jetmax JETSON NANO robotska roka z operacijskim sistemom ROS: https://www.hiwonder.hk/collections/jetson/products/hiwonder-jetmax-jetson-nano-robot-arm-ros-open-source-vision-recognition-program-robot

## HTTP strežnik za komunikacijo z robotsko roko

https://github.com/fsprojekti/shr-mfg-robotic-arm-http-server

## ESP32 plošča

joy-it SBC NodeMCU-ESP32 plošča: https://joy-it.net/en/products/SBC-NodeMCU-ESP32

Glavne značilnosti:
* procesor: Tensilica LX6 Dual-Core, 240 MHz
* spomin: 4 MB, SRAM: 512 kb
* wifi: 802.11 b/g/n, 2,4 GHz
* bluetooth: classic/LE
* vmesniki: UART, I2C, SPI, DAC, ADC
* delovna napetost: 3,3 V (5 V microUSB)

Priročnik: https://joy-it.net/files/files/Produkte/SBC-NodeMCU-ESP32/SBC-NodeMCU-ESP32-Manual-2021-06-29.pdf

## Razvojno okolje Arduino

Arduino IDE: https://www.arduino.cc/en/software

Zahtevane namestitve:
* ESP32 board
	* dodaj https://dl.espressif.com/dl/package_esp32_index.json na seznam Additional Boards Manager URLs v nastavitvah Arduino IDE (Preferences)
	* select 
* knjižnica WiFi (za komunikacijo med osebnim računalnikom in robotsko roko)
* knjižnica ESPmDNS (za podporo DNS zahtevtkom na ESP čipu)
* knjižnica WebServer (če želimo lokalni strežnik za dohodne HTTP zahtevke)
* knjižnica HTTPClient (za pošiljanje izhodnih HTTP sporočil)
* knjižnica ArduinoJson library (za oblikovanje HTTP sporočil v JSON formatu)

Povezava na WiFi omrežje:
* nastavitev imena omrežja in gesla za dostop (izven setup in loop funkcij):
	* const char* ssid     = "IME OMREŽJA";
	* const char* password = "GESLO";
* vzpostavitev povezave (v setup funkciji):
	* WiFi.begin(ssid, password);
	* while (WiFi.status() != WL_CONNECTED) {
		delay(500);
		Serial.print(".");
	  }
	* Serial.println(WiFi.localIP());  (dodeljeni IP naslov v WiFi omrežju)
	
Pošiljanje HTTP zahtevkov na robotsko roko:
* ustvarjanje HTTP klienta: <code>HTTPClient http;</code>
* ustvarjanje HTTP sporočila: <code>http.begin(roboticArmHttpApiIp, roboticArmHttpApiPort, "/");</code>
* pošiljanje HTTP sporočila: <code>int httpCode = http.GET();</code>
* preverjanje odgovora:
	* // v primeru napake je HTTP koda negativna
    </code>if (httpCode > 0) {
        // HTTP header has been send and Server response header has been handled
        Serial.println("HTTP response code: " + String(httpCode));
        Serial.println("HTTP response: " + http.getString());

    }
    // error sending HTTP request, print error messasge
    else {
        Serial.println("HTTP response code: " + String(httpCode));
        Serial.println("HTTP GET failed, error:");
        Serial.println(http.errorToString(httpCode).c_str());
    }</code>
