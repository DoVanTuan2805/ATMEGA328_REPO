#include <SoftwareSerial.h>

#define RS485RX 2  //Serial Receive pin
#define RS485TX 3  //Serial Transmit pin

#define LED 13
#define BUTTON 4
SoftwareSerial RS485(RS485RX, RS485TX);  // RX, TX
char byteReceived[4];

byte masterAdress = 0x00;
byte SlaveAdress = 0x02;

byte Rx = 0x03;
byte Tx = 0x04;

byte EnableLight = 0x05;  // ON OFF
byte EnableValue = 0x06;  // float value

byte On = 0x01;
byte Off = 0x00;

bool onOff;

float value = 12.50;
byte data[8];
byte dataValue[8];
uint64_t prev;
bool stateButton;

void setup() {
  Serial.begin(4800);
  RS485.begin(4800);
  pinMode(LED, OUTPUT);
  pinMode(BUTTON, INPUT_PULLUP);
  
}
byte dataFloat[4];
void loop() {
  if (millis() - prev >= 2000) {
    *(float*)dataFloat = value;
    prev = millis();
  }


  while (RS485.available())  //tìm dữ liệu từ thiết bị khác truyền về
  {
    int lenRS = RS485.readBytes(byteReceived, 5);  // đọc byte nhận được
    //Serial.write(byteReceived, lenRS);
    if (byteReceived[0] == masterAdress) {       // 0X00
      if (byteReceived[1] == SlaveAdress) {      // 0X01
        if (byteReceived[2] == Rx) {             // 0X03
          if (byteReceived[3] == EnableLight) {  // 0X05
            if (byteReceived[4] == On) {         // 0X01
              data[0] = masterAdress;
              data[1] = SlaveAdress;
              data[2] = Tx;
              data[3] = EnableLight;
              data[4] = On;
              onOff = true;
              RS485.write(data, 4);
              memset(data, 0, sizeof(data));
            } else if (byteReceived[4] == Off) {
              data[0] = masterAdress;
              data[1] = SlaveAdress;
              data[2] = Tx;
              data[3] = EnableLight;
              data[4] = Off;
              onOff = false;
              RS485.write(data, 4);
              memset(data, 0, sizeof(data));
            }
          }
        }
        if (byteReceived[2] == Tx) {
          if (byteReceived[3] == EnableValue) {
            memcpy(dataValue + 4, &dataFloat, sizeof(float));
            dataValue[0] = masterAdress;
            dataValue[1] = SlaveAdress;
            dataValue[2] = Rx;
            dataValue[3] = EnableValue;
            
            RS485.write(dataValue, 8);
            Serial.write(dataValue, 8);
            memset(dataValue, 0, sizeof(dataValue));
          }
        }
      }
    }
    memset(byteReceived, 0, sizeof(byteReceived));
  }
  digitalWrite(LED, onOff);
}