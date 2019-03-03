#include <ESP8266WiFi.h>          //https://github.com/esp8266/Arduino
#include <DNSServer.h>            //https://github.com/esp8266/Arduino
#include <ESP8266WebServer.h>     //https://github.com/esp8266/Arduino
#include <IRremoteESP8266.h>      //https://github.com/markszabo/IRremoteESP8266
#include <ProntoHex.h>            //https://github.com/probonopd/ProntoHex
#include "WiFiManager.h"          //https://github.com/tzapu/WiFiManager

// Configure Ditigal PIN
// D3 is used with the wemos IR shield: https://wiki.wemos.cc/products:d1_mini_shields:ir_controller_shield
IRsend irsend(D3);
char* hostname = "Wifi-IR";

ProntoHex ph = ProntoHex();       //Prontohex.
ESP8266WebServer serverHttp(80);  //HTTP service.
WiFiServer serverTcp(23);         //TCP service.

void configModeCallback (WiFiManager *myWiFiManager) {
  Serial.println(F("Entered config mode"));
  Serial.println(WiFi.softAPIP());
  Serial.println(myWiFiManager->getConfigPortalSSID());
}


void setup() {
  Serial.begin(115200);
  WiFiManager wifiManager;
  //wifiManager.resetSettings(); // Remove stored WiFi Settings.

  wifiManager.setAPCallback(configModeCallback);
  if(!wifiManager.autoConnect(hostname)) {
    Serial.println("failed to connect and hit timeout");
    ESP.reset();
    delay(1000);
  } 
  
  Serial.print(F("Connected to wifi. Using IP: "));
  Serial.println(WiFi.localIP());

  // Start ir library
  irsend.begin();

  // Start the server
  serverHttp.on("/", handleHttpRoot);
  serverHttp.on("/pronto", handleHttpPronto);
  serverHttp.onNotFound(handleHttpRoot);
  serverHttp.begin();
  Serial.println("Http Server started");


  serverTcp.begin();
}

void loop() {
  serverHttp.handleClient();
  handleTcpPronto();
}

void handleHttpRoot() {
 serverHttp.send(200, "text/html", "<body><h1>Wifi-IR, send Pronto HEX formater infrared signals!</h1><form onsubmit=\"window.open('/pronto?code=' + document.getElementById('pronto').value, '_new')\"> Pronto HEX:<br> <input type=\"text\" name=\"code\" id=\"pronto\"><br> <input type=\"submit\" value=\"Send\"> </form> <p> Find IR codes at: <a href=\"http://irdb.tk/find/\">irdb.tk</a> </p></body>");
}

void handleTcpPronto(){
  WiFiClient tcpClient = serverTcp.available();
  
  if (tcpClient) {
    if(tcpClient.connected())
    {
      Serial.println("Client Connected");
    }
    
    while(tcpClient.connected()){      
      while(tcpClient.available()>0){
        // read data from the connected client
        String pronto = tcpClient.readStringUntil('\r');
        boolean didSend = handlePronto(pronto);
        if (didSend) {
          //tcpClient.write("1\r");
        } else {
          //tcpClient.write("Error!\r\n");
        }
      }
      //Send Data to connected client
      while(Serial.available()>0)
      {
        tcpClient.write(Serial.read());
      }
    }
    tcpClient.stop();
    Serial.println("Client disconnected");    
  }
}

void handleHttpPronto(){
  for (uint8_t i=0; i<serverHttp.args(); i++){
    if(serverHttp.argName(i) == "code") 
    {
      boolean didSend = handlePronto(serverHttp.arg(i));
      if (didSend) {
        serverHttp.send(200, "text/html", "OK");
      } else {
        serverHttp.send(200, "text/html", "ERROR");
      }
    }
  }
}

boolean handlePronto(String line){
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
        return true;
      } else {
        return false;
      }
}
