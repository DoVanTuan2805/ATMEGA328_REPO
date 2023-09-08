#include <Servo.h>
#include "SoftwareSerial.h"
#include "DFRobotDFPlayerMini.h"

Servo myServo;
int servoPin = 9;
#define IN1 7
#define IN2 6
#define IN3 5
#define IN4 4
#define MAX_SPEED 255
#define MIN_SPEED 0
SoftwareSerial mySoftwareSerial(2, 3);  //pin RX dan TX
DFRobotDFPlayerMini myDFPlayer;
int pos = 0;

#define thungracday 8

const int trig = 12;  // chân trig của HC-SR04
const int echo = 11;  // chân echo của HC-SR04

float GetDistance() {
  unsigned long duration;  // biến đo thời gian
  int distanceCm;          // biến lưu khoảng cách

  /* Phát xung từ chân trig */
  digitalWrite(trig, 0);  // tắt chân trig
  delayMicroseconds(2);
  digitalWrite(trig, 1);  // phát xung từ chân trig
  delayMicroseconds(2);   // xung có độ dài 5 microSeconds
  digitalWrite(trig, 0);  // tắt chân trig

  /* Tính toán thời gian */
  // Đo độ rộng xung HIGH ở chân echo.
  duration = pulseIn(echo, HIGH);
  // Tính khoảng cách đến vật.
  distanceCm = int(duration / 2 / 29.412);
  delay(5);
  return distanceCm;
}

void setup() {
  Serial.begin(9600);
  myServo.attach(servoPin);
  myServo.write(0);
  pinMode(thungracday, INPUT);
  pinMode(trig, OUTPUT);  // chân trig sẽ phát tín hiệu
  pinMode(echo, INPUT);   // chân echo sẽ nhận tín hiệu
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  mySoftwareSerial.begin(9600);
  if (!myDFPlayer.begin(mySoftwareSerial, true, false)) {
    while (true) {
      delay(0);
    }
  }
  myDFPlayer.volume(30);  // cài đặt âm lượng từ 0-30
  myDFPlayer.play(1);
  delay(2000);  // khi cắm điện thì âm thanh khởi động được kích hoạt (bài 1)
}

void loop() {
  static unsigned long t_prev = 0, t_prevWash = 0;
  static bool time_wash = 0;
  static int time_w = 0;
  if (digitalRead(amthanh) == 0) {
    delay(5);
    tt = !tt;
    while (digitalRead(amthanh) == 0) {
      delay(50);
    }
  }
  if (!tt) {
    Serial.println("di thang 1");
    motor_1_Tien(MAX_SPEED);
    motor_2_Tien(MAX_SPEED);
  }
  if (tt) {
    motor_1_Dung();
    motor_2_Dung();
    long distance = GetDistance();
    if ((distance < 25) && (digitalRead(thungracday) == HIGH)) {
      mo_thung_rac();
      am_thanh_mo_thung_rac();
      time_wash = 1;
    }
    if ( time_wash == 1) {
      dong_thung_rac();
      am_thanh_dong_thung_rac();
      if (millis() - t_prevWash > 2000) {
        time_wash = 0;
        t_prevWash = millis();
      }
    }
    if ((distance < 25) && (digitalRead(thungracday) == LOW)) {
      am_thanh_thung_rac_day();  // lựa chọn 1: khi thùng rác đầy thì chỉ phát ra âm thanh và không mở thùng rác
      mo_thung_rac();    // lựa chọn 2: khi thùng rác đầy thì vẫn mở thùng rác và phát âm thanh thùng rác đầy
    }
  }
}

void mo_thung_rac() {
  for (pos = 0; pos <= 135; pos += 1)  // Góc mở của servo (nắp thùng rác) từ 0-180
  {
    myServo.write(pos);  // yêu cầu servo chuyển đến vị trí trong biến 'pos'
    delay(3);            // điều chỉnh thông số này để thay đổi tốc độ mở thùng rác
  }
}
void dong_thung_rac() {
  for (pos = 135; pos >= 0; pos -= 1)  // Góc mở của servo (nắp thùng rác) từ 0-180
  {
    myServo.write(pos);  // yêu cầu servo chuyển đến vị trí trong biến 'pos'
    delay(3);            // điều chỉnh thông số này để thay đổi tốc độ đóng thùng rác
  }
}

void am_thanh_mo_thung_rac()  //khi thùng rác mở thì sẽ phát âm thanh (2)
{
  myDFPlayer.play(2);
}

void am_thanh_dong_thung_rac()  //khi thùng rác mở thì sẽ phát âm thanh (3)
{
  myDFPlayer.play(3);
}
void am_thanh_thung_rac_day()  //khi thùng rác mở thì sẽ phát âm thanh (4)
{
  myDFPlayer.play(4);
}
void motor_1_Dung() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
}

void motor_2_Dung() {
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
}

void motor_1_Tien(int speed) {
  speed = constrain(speed, MIN_SPEED, MAX_SPEED);
  digitalWrite(IN1, HIGH);
  analogWrite(IN2, 255 - speed);
}

void motor_1_Lui(int speed) {
  speed = constrain(speed, MIN_SPEED, MAX_SPEED);
  digitalWrite(IN1, LOW);
  analogWrite(IN2, speed);
}

void motor_2_Tien(int speed) {
  speed = constrain(speed, MIN_SPEED, MAX_SPEED);
  analogWrite(IN3, speed);
  digitalWrite(IN4, LOW);
}

void motor_2_Lui(int speed) {
  speed = constrain(speed, MIN_SPEED, MAX_SPEED);
  analogWrite(IN3, 255 - speed);
  digitalWrite(IN4, HIGH);
}
