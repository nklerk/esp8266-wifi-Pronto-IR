#include <ESP8266WiFi.h>          //https://github.com/esp8266/Arduino
#include <DNSServer.h>            //https://github.com/esp8266/Arduino
#include <ESP8266WebServer.h>     //https://github.com/esp8266/Arduino
#include <IRremoteESP8266.h>      //https://github.com/markszabo/IRremoteESP8266
#include <ProntoHex.h>            //https://github.com/probonopd/ProntoHex
#include "WiFiManager.h"          //https://github.com/tzapu/WiFiManager

// Configure Ditigal PIN
// D4 is used because it is next to the ground pin on Wemos D1 Mini.
IRsend irsend(D4);
char* hostname = "Wifi-IR";

ProntoHex ph = ProntoHex();       //Prontohex.
ESP8266WebServer server(80);      //default web service.

void configModeCallback (WiFiManager *myWiFiManager) {
  Serial.println("Entered config mode");
  Serial.println(WiFi.softAPIP());
  Serial.println(myWiFiManager->getConfigPortalSSID());
}

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  
  WiFiManager wifiManager;
  //wifiManager.resetSettings();

  wifiManager.setAPCallback(configModeCallback);
  if(!wifiManager.autoConnect(hostname)) {
    Serial.println("failed to connect and hit timeout");
    ESP.reset();
    delay(1000);
  } 
  
  Serial.print("Connected to wifi. Using IP: ");
  Serial.println(WiFi.localIP());

  // Start ir library
  irsend.begin();

  // Start the server
  server.on("/", handleRoot);
  server.on("/pronto", handlePronto);
  server.onNotFound(handleRoot);
  server.begin();
  Serial.println("Server started");
}

void loop() {
  server.handleClient();
  // END
}

void handleRoot() {
 server.send(200, "text/html", "<body><h1>Wifi-IR, send Pronto HEX formater infrared signals!</h1><form onsubmit=\"window.open('/pronto?code=' + document.getElementById('pronto').value, '_new')\"> Pronto HEX:<br> <input type=\"text\" name=\"code\" id=\"pronto\"><br> <input type=\"submit\" value=\"Send\"> </form> <p> Find IR codes at: <a href=\"http://irdb.tk/find/\">irdb.tk</a> </p></body>");
}

void handlePronto(){
  for (uint8_t i=0; i<server.args(); i++){
    if(server.argName(i) == "code") 
    {
      String line = server.arg(i);
      line.trim();
      if (line.startsWith("0000 ")) // Then we assume it is Pronto Hex
      {
        Serial.println("Convert PRONTO");
        ph.convert(line);
        Serial.print("Received PRONTO: ");
        Serial.println(line);
        Serial.print("Len:");
        Serial.println(ph.length);
        Serial.println("irsend.sendRaw()");
        irsend.sendRaw(ph.convertedRaw, ph.length, ph.frequency);
        server.send(200, "text/html", "OK");
      } else {
        server.send(200, "text/html", "ERROR");
      }
    }
  }
}
