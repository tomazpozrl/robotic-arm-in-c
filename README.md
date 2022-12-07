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

Required installations:
* ESP32 board
	* add https://dl.espressif.com/dl/package_esp32_index.json to the Additional Boards Manager URLs list in Preferences section of Arduino IDE
	* select 
* WiFi library (for communication via WiFi)
* ESPmDNS library (for DNS query support on ESP chip)
* WebServer library (if a local server will be run for incoming requests)
* HTTPClient library (for sending outgoing HTTP messages)
* ArduinoJson library (for formatting HTTP message in JSON format)

