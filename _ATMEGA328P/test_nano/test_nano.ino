#include <Servo.h>
Servo motor;
#define mt 6
int val;
int speeds;
void setup(){
  Serial.begin(9600);
  motor.attach(mt, 1000, 2000);
}
void loop(){
  val = analogRead(A1);

  speeds = map(val, 0 , 1023,0, 180);
  motor.write(speeds);
  Serial.println(speeds);
  delay(100);
}
