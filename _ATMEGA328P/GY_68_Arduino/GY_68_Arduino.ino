#include <Wire.h>
#include <Adafruit_BMP085.h>
#define led1 2
#define led2 3
Adafruit_BMP085 bmp;
String data_rx = "";
String vs_min, vs_max;
unsigned long vi_min , vi_max, pressure;
void setup() {
  Serial.begin(9600);
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  if (!bmp.begin()) {
    Serial.println("Could not find a valid BMP085 sensor, check wiring!");
    while (1) {}
  }
}
void loop() {
  static unsigned long t_prev = 0;
  pressure = bmp.readPressure();
  if (Serial.available()) {
    data_rx = Serial.readStringUntil('\n');
    vs_min = getValue(data_rx, '/', 0);
    vs_max = getValue(data_rx, '/', 1);
    vi_min = vs_min.toInt();
    vi_max = vs_max.toInt();
  }
  if (millis() - t_prev >= 500) {
    Serial.println(pressure);
    t_prev = millis();
  }
  check(pressure, vi_min, vi_max);
}
void check(unsigned long values, unsigned long mins , unsigned long maxs ) {
  if (values < mins || values > maxs ) {
    digitalWrite(led1, HIGH);
    digitalWrite(led2, LOW);
  }
  else {
    digitalWrite(led1, LOW);
    digitalWrite(led2, HIGH);
  }
}
String getValue(String data, char separator, int index) {
  int found = 0;
  int strIndex[] = { 0, -1 };
  int maxIndex = data.length() - 1;
  for (int i = 0; i <= maxIndex && found <= index; i++) {
    if (data.charAt(i) == separator || i == maxIndex) { //data.charAt(i) xuất ra kí tự ở vị trí (i)
      found++;
      strIndex[0] = strIndex[1] + 1;
      strIndex[1] = (i == maxIndex) ? i + 1 : i;
      // (i == maxIndex) true -> i + 1
      // (i == maxIndex) false -> i
    }
  }
  return found > index ? data.substring( strIndex[0], strIndex[1] ) : "";
}
