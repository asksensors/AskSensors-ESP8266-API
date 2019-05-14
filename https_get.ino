/*
 * askSensors HTTPS Request
 * Description: Connect ESP8266 to AskSensors over HTTPS GET Request.
 *  Author: https://asksensors.com, 2018
 */

// includes
#include <ESP8266WiFi.h>
#include <WiFiClientSecure.h>

// Wifi config
const char* wifi_ssid = "..........";             // SSID
const char* wifi_password = "..........";         // WIFI
const unsigned int writeInterval = 25000;   // write interval (in ms)

// ASKSENSORS config.
String host = "api.asksensors.com"; // ASKSENSORS API host name
const int https_port = 443;                        // https port
const char* https_fingerprint =  "B5 C3 1B 2C 0D 5D 9B E5 D6 7C B6 EF 50 3A AD 3F 9F 1E 44 75";     // ASKSENSORS HTTPS SHA1 certificate
const char* apiKeyIn = "..........";      // API KEY IN, example: FALOAPPKH17ZR4Q23A8U9W0XPJL0F6OG

// create ASKSENSORS client
WiFiClientSecure client;

void setup() {
  Serial.begin(115200);
  Serial.println();
  Serial.print("********** connecting to WIFI : ");
  Serial.println(wifi_ssid);
  WiFi.begin(wifi_ssid, wifi_password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("-> WiFi connected");
  Serial.println("-> IP address: ");
  Serial.println(WiFi.localIP());
  // Set Client to insecure
  client.setInsecure();
 
}

void loop() {
// Use WiFiClientSecure class to create TLS connection
  Serial.print("********** connecting to HOST : ");
  Serial.println(https_host);
  if (!client.connect(https_host, https_port)) {
    Serial.println("-> connection failed");
    //return;
  }
  
  // Create a URL for the request
  String url = "/write/";
  url += apiKeyIn;
  url += "?module1=";
  url += random(10,100);
  
  Serial.print("********** requesting URL: ");
  Serial.println(url);

  client.print(String("GET ") + url + " HTTP/1.1\r\n" +
               "Host: " + https_host + "\r\n" +
               "Connection: close\r\n\r\n");

  Serial.println("> Request sent to ASKSENSORS");
  while (client.connected()) {
    String line = client.readStringUntil('\n');
    if (line == "\r") {
        String line = client.readStringUntil('\n');
        Serial.println("********** ASKSENSORS replay:");
        Serial.println(line);
        Serial.println("********** closing connection");
      
        break;
    }
  }

  delay(writeInterval);     // delay 25sec
}
