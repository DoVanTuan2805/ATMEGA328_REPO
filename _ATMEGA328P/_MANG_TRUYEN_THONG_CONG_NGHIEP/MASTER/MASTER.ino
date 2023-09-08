#include <SoftwareSerial.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);  // set the LCD address to 0x27 for a 16 chars and 2 line display

#define RS485RX 2  //Serial Receive pin
#define RS485TX 3  //Serial Transmit pin

#define LED 13
#define BUTTON1 8
#define BUTTON2 9
#define BUTTON3 10
SoftwareSerial RS485(RS485RX, RS485TX);  // RX, TX
char byteReceived[8];
byte masterAdress = 0x00;
byte slaveAdress[5] = { 0x01, 0x02, 0x03, 0x04, 0x05 };

byte Rx = 0x04;
byte Tx = 0x03;

byte EnableLight = 0x05;  // ON OFF
byte EnableData = 0x06;   // float value

byte On = 0x01;
byte Off = 0x00;

bool onOff;

int value;
byte data[7];
byte dataTx[5];
byte dataRx[4];
uint64_t prev;

byte myBytes[4];

typedef struct {
  bool stateButton;
  int prevButton;
  int currButton;
  unsigned long pressed;
  unsigned long released;
} Button_t;
Button_t bt1, bt2, bt3;

uint16_t ttDataRx;

void setup() {
  Serial.begin(4800);
  RS485.begin(4800);
  lcd.init();
  lcd.backlight();

  pinMode(LED, OUTPUT);
  pinMode(BUTTON1, INPUT_PULLUP);
  pinMode(BUTTON2, INPUT_PULLUP);
  pinMode(BUTTON3, INPUT_PULLUP);
  
}

void loop() {
  while (RS485.available() != 0) {
    int len = RS485.readBytes(byteReceived, 8);
    //Serial.println(len);
    Serial.write(byteReceived, len);
    if (byteReceived[0] = masterAdress) {
      if (byteReceived[1] == slaveAdress[0]) {
        if (byteReceived[2] == Tx) {
          if (byteReceived[3] == EnableData) {
          }
        }
      }
    }
    memset(byteReceived, 0, sizeof(byteReceived));
  }
  controlSlave(&bt1, BUTTON1);
  controlSlave(&bt2, BUTTON2);
  controlSlave(&bt3, BUTTON3);
  if (millis() - prev > 5000) {
    prev = millis();
    ttDataRx++;
    dataRx[0] = masterAdress;
    dataRx[2] = Rx;
    dataRx[3] = EnableData;
    if (ttDataRx < 3) {
      dataRx[1] = slaveAdress[0];
      //RS485.write(dataRx, sizeof(dataRx));
      //Serial.write(dataRx, sizeof(dataRx));
    } else if (ttDataRx >= 3) {
      ttDataRx = 0;
    }
    memset(dataRx, 0, sizeof(dataRx));
  }
}

void controlSlave(Button_t *bt, uint16_t BUTTON) {
  dataTx[0] = masterAdress;
  dataTx[2] = Tx;
  dataTx[3] = EnableLight;
  if (BUTTON == BUTTON1) {
    dataTx[1] = slaveAdress[0];
  }
  if (BUTTON == BUTTON2) {
    dataTx[1] = slaveAdress[1];
  }
  if (BUTTON == BUTTON3) {
    dataTx[1] = slaveAdress[2];
  }
  bt->currButton = digitalRead(BUTTON);
  if (bt->prevButton == HIGH && bt->currButton == LOW) {  // button is pressed
    Serial.println("Press");
    bt->pressed = millis();
  } else if (bt->prevButton == LOW && bt->currButton == HIGH) {  // button is released
    Serial.println("Release");
    bt->released = millis();
    long pressDuration = bt->released - bt->pressed;
    if (pressDuration > 20) {
      if (bt->stateButton == true) {
        dataTx[4] = Off;
        RS485.write(dataTx, sizeof(dataTx));
        memset(dataTx, 0, sizeof(dataTx));
        bt->stateButton = false;
      } else if (bt->stateButton == false) {
        dataTx[4] = On;
        RS485.write(dataTx, sizeof(dataTx));
        memset(data, 0, sizeof(dataTx));
        bt->stateButton = true;
      }
    }
  }
  bt->prevButton = bt->currButton;
}