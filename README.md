# esp8266-wifi-Pronto-IR
A arduino project that makes it possible to send IR codes over a WiFi connection.
This project will set you back somewhere between 2$ and 4$. If you like this project then please donate: https://www.paypal.me/NielsdeKlerk

## Requirements:
- A Wemos D1 Mini (ESP8266) or similar.
  -- https://wiki.wemos.cc/products:d1:d1_mini
  -- http://tiny.cc/zzvj3y
- A Wemos IR Controller Shield
  -- https://wiki.wemos.cc/products:d1_mini_shields:ir_controller_shield
  -- https://tinyurl.com/y6oelkry
- Prototype board, Prototype cables. or a soldering station.
- Arduino IDE installed on your computer. -> https://www.arduino.cc/en/main/software

## Build your project.
Place the IR controller to the D1 Mini.
(or use a IR LED)

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
- Connect your computer or your mobile phone to the wifi network named "Wifi-Ir".
- The wifi connection wizard will automatically open.

## Usage.

### Connect using a brouwser to
http://<ipaddress of wifi-ir>/

### Connect using the API:
http://<ipaddress of wifi-ir>/pronto?code=<PRONTO HEX>

Example:
http://192.168.1.90/pronto?code=0000 006C 0022 0002 015B 00AD 0016 0016 0016 0041 0016 0016 0016 0016 0016 0041 0016 0016 0016 0041 0016 0041 0016 0041 0016 0016 0016 0041 0016 0041 0016 0016 0016 0041 0016 0041 0016 0016 0016 0041 0016 0016 0016 0041 0016 0016 0016 0016 0016 0016 0016 0016 0016 0016 0016 0016 0016 0041 0016 0016 0016 0041 0016 0041 0016 0041 0016 0041 0016 0041 0016 05CB 015B 0057 0016 0E6C

### Connect using a TCP session (telnet)

This is the fastest connection method. (low latency)

- Connect using telnet port 23
- Send the prontoHex and end with a return character (\r)

### Discover using mDNS

The code generates a unique hostname. Wifi-IR_...... where the ...... represent the unique id.
The http based API can be discovered using _wifi-ir-http._tcp.
The telnet based API The hcan be discovered using _wifi-ir-telnet._tcp.
