#include <SoftwareSerial.h>

#define RS485RX 3  //Serial Receive pin
#define RS485TX 2  //Serial Transmit pin

#define LED 13
#define BUTTON 4
SoftwareSerial RS485(RS485RX, RS485TX);  // RX, TX
char byteReceived[4];
byte SlaveAdress = 0x01;

byte Rx = 0x03;
byte Tx = 0x04;

byte EnableOnOff = 0x05;  // ON OFF
byte EnableValue = 0x06;  // float value

byte On = 0x01;
byte Off = 0x00;

bool onOff;

int prevButton = LOW;
int currButton;
unsigned long pressed = 0;
unsigned long released = 0;

int value;
byte data[7]; 

uint64_t prev;
bool stateButton;

void setup() {
  Serial.begin(9600);
  pinMode(LED, OUTPUT);
  pinMode(BUTTON, INPUT_PULLUP);
  RS485.begin(9600);
  prevButton = HIGH;
}

void loop() {

  currButton = digitalRead(BUTTON);

  if (prevButton == HIGH && currButton == LOW) {  // button is pressed
    pressed = millis();
  } else if (prevButton == LOW && currButton == HIGH) {  // button is released
    released = millis();
    long pressDuration = released - pressed;
    if (pressDuration > 20) {
      if (stateButton == true) {
        data[0] = SlaveAdress;
        data[1] = Tx;
        data[2] = EnableOnOff;
        data[3] = Off;
        RS485.write(data, sizeof(data));
        memset(data, 0, sizeof(data));
        stateButton = false;
      } else if (stateButton == false) {
        data[0] = SlaveAdress;
        data[1] = Tx;
        data[2] = EnableOnOff;
        data[3] = On;
        RS485.write(data, sizeof(data));
        memset(data, 0, sizeof(data));
        stateButton = true;
      }
    }
  }
  prevButton = currButton;

  if (millis() - prev >= 4500) {
    value = random(0, 50);

    data[0] = SlaveAdress;
    data[1] = Tx;  // 0xFA
    data[2] = EnableValue;

    memcpy(data + 3, &value, sizeof(int));
    RS485.write(data, 7);
    memset(data, 0, sizeof(data));
    prev = millis();
  }


  while (RS485.available())  //tìm dữ liệu từ thiết bị khác truyền về
  {
    int lenRS = RS485.readBytes(byteReceived, 4);  // đọc byte nhận được
    Serial.write(byteReceived, lenRS);
    if (byteReceived[0] == SlaveAdress) { // 0X10
      if (byteReceived[1] == Rx) { // 0X0F
        if (byteReceived[2] == EnableOnOff) { // 0X50
          if (byteReceived[3] == On) {  // 0X01
            data[0] = SlaveAdress;
            data[1] = Tx;
            data[2] = EnableOnOff;
            data[3] = On;
            RS485.write(data, 4);
            memset(data, 0, sizeof(data));
            stateButton = true;
          } else if (byteReceived[3] == Off) {
            data[0] = SlaveAdress;
            data[1] = Tx;
            data[2] = EnableOnOff;
            data[3] = Off;
            RS485.write(data, 4);
            memset(data, 0, sizeof(data));
            stateButton = false;
          }
          
        }
      }
    }
    memset(byteReceived, 0, sizeof(byteReceived));
  }
  digitalWrite(LED, stateButton);
}