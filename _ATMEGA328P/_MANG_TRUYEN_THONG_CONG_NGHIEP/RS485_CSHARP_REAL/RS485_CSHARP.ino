#include <SoftwareSerial.h>
#define RX 2
#define TX 3

#define LED 13
#define BT 4
SoftwareSerial rs485(RX, TX); // RX, TX
char dataRead[3];

// byte adress = 0x01;
// byte adress = 0x02;
byte adress = 0x03;

byte Enable_Rx = 0x05;
byte Enable_Tx = 0x06;
byte On = 0x01;
byte Off = 0x00;

bool onOff;

int lastState = LOW;
int currentState;
unsigned long pressedTime = 0;
unsigned long releasedTime = 0;

void setup()
{
  Serial.begin(9600);
  pinMode(LED, OUTPUT);
  pinMode(BT, INPUT_PULLUP);
  rs485.begin(115200);
  lastState = HIGH;
}
float value;
byte data[7]; // Khởi tạo mảng byte
byte numberTx[4];

uint64_t prev;
bool stateButton;
void loop()
{

  currentState = digitalRead(BT);

  if (lastState == HIGH && currentState == LOW)
  { // button is pressed
    pressedTime = millis();
  }
  else if (lastState == LOW && currentState == HIGH)
  { // button is released
    releasedTime = millis();
    long pressDuration = releasedTime - pressedTime;
    if (pressDuration > 20)
    {
      if (stateButton == true)
      {
        data[0] = adress;
        data[1] = Enable_Tx;
        data[2] = Off;
        rs485.write(data, sizeof(data));
        memset(data, 0, sizeof(data));
        stateButton = false;
      }
      else if (stateButton == false)
      {
        data[0] = adress;
        data[1] = Enable_Tx;
        data[2] = On;
        rs485.write(data, sizeof(data));
        memset(data, 0, sizeof(data));
        stateButton = true;
      }
    }
  }
  lastState = currentState;
  while (rs485.available())
  {
    int lenRS = rs485.readBytes(dataRead, 3);

    if (dataRead[0] == adress)
    {
      if (dataRead[1] == Enable_Rx)
      {
        Serial.write(dataRead, 7);
        if (dataRead[2] == On)
        {
          data[0] = adress;
          data[1] = Enable_Tx;
          data[2] = On;
          stateButton = true;
        }
        else if (dataRead[2] == Off)
        {
          data[0] = adress;
          data[1] = Enable_Tx;
          data[2] = Off;
          stateButton = false;
        }
        rs485.write(data, sizeof(data));
        memset(data, 0, sizeof(data));
      }
    }
    memset(dataRead, 0, 3);
  }
  digitalWrite(LED, stateButton);
}