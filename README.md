# esp8266-wifi-Pronto-IR
A arduino project that makes it possible to send IR codes over a WiFi connection.
This project will set you back somewhere around 2$. If you like this project then please donate: https://www.paypal.me/NielsdeKlerk

## Requirements:
- A Wemos D1 Mini (ESP8266) or similar.
  http://tiny.cc/zzvj3y
- A 940nm ifrared LED. (~3V)
- Prototype board, Prototype cables. or a soldering station.
- Arduino IDE installed on your computer. -> https://www.arduino.cc/en/main/software

## Build your project.
Connect the IR LED to the wemos D1 Mini.
The LED has two legs a showr and longer lag.
Connect the short leg to the ground pin.
Connect the long leg to the D2 pin.

## Program the code.
- open the arduino IDE.
- Add ESP8266 support ising the boards manager. https://github.com/esp8266/Arduino#installing-with-boards-manager
- Install IRremote. https://github.com/markszabo/IRremoteESP8266#official-releases-via-the-arduino-ide-v18-windows--linux
- Install ProntoHex. https://github.com/probonopd/ProntoHex
- Install WiFi Manager. https://github.com/tzapu/WiFiManager#install-through-library-manager

- Connect the wemos D1 mini with USB to your computer.
- Open the wifi-ir.ino file in Arduino IDE.
- Goto Tools, Select the board "LOLIN (Wemos) D1 R2 & mini".
- Goto Tools, Select the serial port.
- Goto Sketch Upload. the Sketch will now upload to the microcontroller.


## First run.
Connect your computer or your mobile phone to the wifi network named Wifi-Ir
Follow the instuctions to setup wifi.

## Usage.

### Connect using a brouwser to
http://<ipaddress of wifi-ir>/

#### Connect using the API:
http://<ipaddress of wifi-ir>/pronto?code=<PRONTO HEX>

Example:
http://192.168.1.90/pronto?code=0000 006C 0022 0002 015B 00AD 0016 0016 0016 0041 0016 0016 0016 0016 0016 0041 0016 0016 0016 0041 0016 0041 0016 0041 0016 0016 0016 0041 0016 0041 0016 0016 0016 0041 0016 0041 0016 0016 0016 0041 0016 0016 0016 0041 0016 0016 0016 0016 0016 0016 0016 0016 0016 0016 0016 0016 0016 0041 0016 0016 0016 0041 0016 0041 0016 0041 0016 0041 0016 0041 0016 05CB 015B 0057 0016 0E6C
