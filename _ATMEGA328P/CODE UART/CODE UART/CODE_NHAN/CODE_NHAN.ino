#include <SoftwareSerial.h>
SoftwareSerial mySerial(D6, D5);
//[D6(RX) - D5(TX)] - [TX -RX]
#include <ArduinoJson.h>

void setup() {
  // Initialize Serial port
  Serial.begin(9600);
  mySerial.begin(115200);
  while (!Serial) continue;

}

void loop() {
  StaticJsonBuffer<1000> jsonBuffer;
  JsonObject& root = jsonBuffer.parseObject(mySerial);
  if (root == JsonObject::invalid())
    return;

  Serial.println("JSON received and parsed");
  root.prettyPrintTo(Serial);
  Serial.print("Data 1 ");
  Serial.println("");
  int data1 = root["temp"];
  Serial.print(data1);
  Serial.print("   Data 2 ");
  int data2 = root["hum"];
  int data3 = root["hi"];
  int data4 = root["namhai"];
  Serial.print(data2);
  Serial.print(data3);
  Serial.print(data4);
  Serial.println("");
  Serial.println("---------------------xxxxx--------------------");

}
