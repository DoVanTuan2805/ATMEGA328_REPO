#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>
#include <Wire.h>

Adafruit_MPU6050 mpu;
String data_tx;
float angleX, angleY, angleZ;
unsigned long prev_time = 0;
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
//  if (!mpu.begin()) {
//    Serial.println("Failed to find MPU6050 chip");
//    while (1) {
//      delay(10);
//    }
//  }
}

void loop() {
//  sensors_event_t a, g, temp;
//  mpu.getEvent(&a, &g, &temp);
//  angleX = a.acceleration.x;
//  angleY = a.acceleration.y;
//  angleZ = a.acceleration.z;

  angleX = random(-10, 10) * 1.01;
  angleY = random(-10, 10) * 1.02;
  angleZ = random(-10, 10) * 1.03;
  delay(50);
  if (millis() - prev_time > 200) {
    data_tx = String(angleX) + "/" + String(angleY) + "/" + String(angleZ);
    //data_tx = String(angleX) + "/" + String(angleY) + "/" + String(angleZ);
    Serial.println(data_tx);
    prev_time = millis();
  }
}
