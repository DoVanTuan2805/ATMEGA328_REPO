#include <SoftwareSerial.h>
#include <ArduinoJson.h>
SoftwareSerial mySerial(5, 6); // [ 5(RX) - 6(TX) ] [TX - RX]
#include "DHT.h"
#define DHTPIN 2
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);

void setup() {
  mySerial.begin(115200);
  pinMode(A0, INPUT);
  dht.begin();
}
StaticJsonBuffer<1000> jsonBuffer;
JsonObject& root = jsonBuffer.createObject();
void loop() {

  float h = dht.readHumidity();
  // Read temperature as Celsius (the default)
  float t = dht.readTemperature();
  // Read temperature as Fahrenheit (isFahrenheit = true)
  float x = 1.23;
  float k = 234;

  // If the DHT-11 is not connected to correct pin or if it doesnot
  //work no data will be sent
  root["temp"] = t;
  root["hum"] = h;
  root["hi"] = x;
  root["gasv"] = analogRead(A0);
  root["namhai"] = k;

  //cu phai gui di
  if (mySerial.available() > 0)
  {
    root.printTo(mySerial);
  }

}
