#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include "index.h"
#define LED 0
const char* ssid = "NGOC XUAN";
const char* password = "01021967";


ESP8266WebServer server(80);
int led = 0;
int point = 0;
static long time_prev = 0;
static long t_prev = 0;
void handleRoot() {
  String s = webpage;
  server.send(200, "text/html", s);
}
void sensor_data() {

  if (millis() - time_prev >= 2000) {
    point = random(0, 10);
    time_prev = millis();
  }
  String sensor_value = String(point);
  server.send(200, "text/html", sensor_value);
}
void ledred()
{
  led = 1;
  Serial.println("ledred");
  String s = webpage;
  //led_control();
  server.send(200, "text/html", s);
}
void ledgreen()
{
  led = 2;
  Serial.println("ledgreen");
  String s = webpage;
  //led_control();
  server.send(200, "text/html", s);
}
void ledblue()
{
  led = 3;
  Serial.println("ledblue");
  String s = webpage;
  //led_control();
  server.send(200, "text/html", s);
}
void setup(void) {
  Serial.begin(115200);
  WiFi.begin(ssid, password);
  Serial.println("");
  pinMode(LED, OUTPUT);
  while (WiFi.status() != WL_CONNECTED) {
    Serial.println("Connecting...");
    delay(500);
  }
  Serial.println("");
  Serial.print("Connected to ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
  time_prev = millis();
  t_prev = millis();
  server.on("/", handleRoot);
  //server.on("/led_set", led_control);
  server.on("/ledred", ledred);
  server.on("/ledgreen", ledgreen);
  server.on("/ledblue", ledblue);
  server.on("/adcread", sensor_data);
  server.begin();
}
void loop(void) {
  server.handleClient();

  if (millis() - t_prev > 300) {
    Serial.println(led);
    t_prev = millis();
  }
}
