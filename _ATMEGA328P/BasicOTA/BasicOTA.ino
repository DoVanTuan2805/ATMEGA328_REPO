#include <FirebaseESP8266.h>
#include <ESP8266WiFi.h>
#include <ESP8266mDNS.h>
#include <WiFiUdp.h>
#include <ArduinoOTA.h>

#ifndef STASSID
#define STASSID "NGOC XUAN"
#define STAPSK  "01021967"
#endif

FirebaseData dulieu;
String data;

#define led D4
const char* ssid = STASSID;
const char* password = STAPSK;


void setup() {
  Serial.begin(115200);
  Serial.println("Booting");
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  while (WiFi.waitForConnectResult() != WL_CONNECTED) {
    Serial.println("Connection Failed! Rebooting...");
    delay(5000);
    ESP.restart();
  }
  ArduinoOTA.onStart([]() {
    String type;
    if (ArduinoOTA.getCommand() == U_FLASH) {
      type = "sketch";
    } else { // U_FS
      type = "filesystem";
    }

    Serial.println("Start updating " + type);
  });
  ArduinoOTA.onEnd([]() {
    Serial.println("\nEnd");
  });
  ArduinoOTA.onProgress([](unsigned int progress, unsigned int total) {
    Serial.printf("Progress: %u%%\r", (progress / (total / 100)));
  });
  ArduinoOTA.onError([](ota_error_t error) {
    Serial.printf("Error[%u]: ", error);
    if (error == OTA_AUTH_ERROR) {
      Serial.println("Auth Failed");
    } else if (error == OTA_BEGIN_ERROR) {
      Serial.println("Begin Failed");
    } else if (error == OTA_CONNECT_ERROR) {
      Serial.println("Connect Failed");
    } else if (error == OTA_RECEIVE_ERROR) {
      Serial.println("Receive Failed");
    } else if (error == OTA_END_ERROR) {  
      Serial.println("End Failed");
    }
  });
  ArduinoOTA.begin();
  Firebase.begin("test1-fc9fb-default-rtdb.firebaseio.com","QP07qcznXFzfmh36bUj0tBIjFHOyeKBaA8JbzSLR");
  Serial.println("Ready");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
//  Firebase.setInt(dulieu,"data",5);
}

void loop() {
  ArduinoOTA.handle();
//  data = Firebase.getString(dulieu,"/TalkToMe/data");
//  Serial.println(data);
//  if (data == "1")
//  {
//    digitalWrite(D4,HIGH);
//  }
//  if (data == "0")
//  {
//    digitalWrite(D4,LOW);
//  }
//  Firebase.setFloat(dulieu,"/thoigianthuc",millis()/3.0);
//  Firebase.get(dulieu,"/data");
//  delay(100);
}
