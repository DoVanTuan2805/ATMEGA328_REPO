#include <SoftwareSerial.h>

int LAMP = 6;
volatile int dim_val = 100;
#define TX 7
#define RX 8
#define zero 2
String s;

SoftwareSerial mySerial(RX, TX);  // RX, TX
int dimming_time = 0;
bool dataRev;
void setup() {
  pinMode(LAMP, OUTPUT);
  Serial.begin(9600);
  mySerial.begin(9600);
  attachInterrupt(digitalPinToInterrupt(zero), zero_cross, RISING);
}

void loop() {
  while (mySerial.available() > 0) {
    char c = mySerial.read();
    if (c != '.') {  //loại bỏ kí tự
      s += c;
      detachInterrupt(digitalPinToInterrupt(zero));
    }
    if (c == '.') {
      dim_val = s.toInt();
      mySerial.println(dim_val);
      s = "";
      attachInterrupt(digitalPinToInterrupt(zero), zero_cross, RISING);
      break;
    }
  }
}

void zero_cross() {
  dimming_time = map(dim_val, 0, 100, 8000, 500);  // 8000
  // Serial.println(dimming_time);
  delayMicroseconds(dimming_time);
  digitalWrite(LAMP, HIGH);
  delayMicroseconds(250);
  digitalWrite(LAMP, LOW);
}
