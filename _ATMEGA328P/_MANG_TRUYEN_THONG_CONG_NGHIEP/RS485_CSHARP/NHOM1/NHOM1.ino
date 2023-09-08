#include <SoftwareSerial.h>

#define RX_RS485 6
#define TX_RS485 7

#define LED 13
#define BT 8
SoftwareSerial RS485_COM(RX_RS485, TX_RS485);  // RX, TX

byte addressSlave = 0x02;
byte Rx = 0x05;
byte Tx = 0x06;
byte On = 0x01;
byte Off = 0x00;

bool onOff;

int lastState = LOW;
int currentState;
unsigned long pressedTime = 0;
unsigned long releasedTime = 0;
bool tt;
void setup() {
  Serial.begin(9600);
  pinMode(LED, OUTPUT);
  pinMode(BT, INPUT_PULLUP);
  RS485_COM.begin(19200);
  lastState = HIGH;
}

byte dataByte[7];  // Khởi tạo mảng byte
char DATA_READ[5];

uint64_t prev;
bool stateButton;
void loop() {
  while (RS485_COM.available() >0)  //tìm dữ liệu từ thiết bị khác truyền về
  {
    int lenRS = RS485_COM.readBytes(DATA_READ, 3);
    tt = true;
  }
  if(tt == true){
    tt = false;
    if (DATA_READ[0] == addressSlave) { // 01
      //Serial.println("slave 1");
      if (DATA_READ[1] == Rx) { // 05
        //Serial.println("Rx");
        if (DATA_READ[2] == On) {  // 01
          dataByte[0] = addressSlave;
          dataByte[1] = Tx;
          dataByte[2] = On;
          stateButton = true;
        } else if (DATA_READ[2] == Off) { // 00
          dataByte[0] = addressSlave;
          dataByte[1] = Tx;
          dataByte[2] = Off;
          stateButton = false;
        }
        RS485_COM.write(dataByte, 3);
        memset(dataByte, 0, sizeof(dataByte));
      }
    }
    memset(DATA_READ, 0, 3);
  }
  currentState = digitalRead(BT);

  if (lastState == HIGH && currentState == LOW) {  // button is pressed
    pressedTime = millis();
  } else if (lastState == LOW && currentState == HIGH) {  // button is released
    releasedTime = millis();
    long pressDuration = releasedTime - pressedTime;
    if (pressDuration > 20) {
      if (stateButton == true) {
        dataByte[0] = addressSlave;
        dataByte[1] = Tx;
        dataByte[2] = Off;
        RS485_COM.write(dataByte, sizeof(dataByte));
        memset(dataByte, 0, sizeof(dataByte));
        stateButton = false;
      } else if (stateButton == false) {
        dataByte[0] = addressSlave;
        dataByte[1] = Tx;
        dataByte[2] = On;
        RS485_COM.write(dataByte, sizeof(dataByte));
        memset(dataByte, 0, sizeof(dataByte));
        stateButton = true;
      }
    }
  }
  lastState = currentState;
  digitalWrite(LED, stateButton);
}