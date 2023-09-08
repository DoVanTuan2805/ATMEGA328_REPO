#include <SoftwareSerial.h>
#define RX 6
#define TX 7

#define LED 13
#define BT 8
SoftwareSerial rs485_SoftUart(RX, TX); // RX, TX
char dataRX[3];

//byte adress = 0x01;
//byte adress = 0x02;
byte adress = 0x03;

byte Enable_Rx = 0x05;
byte Enable_Tx = 0x06;
byte On = 0x01;
byte Off = 0x00;

bool onOff;

int lastState;
int currentState;
unsigned long pressedTime = 0;
unsigned long releasedTime = 0;

byte data[7]; 

uint64_t prev;
bool ledControl;
void setup()
{
  Serial.begin(9600);
  pinMode(LED, OUTPUT);
  pinMode(BT, INPUT_PULLUP);
  rs485_SoftUart.begin(115200);
  lastState = HIGH;
}

void loop()
{

  currentState = digitalRead(BT);

  if (lastState == HIGH && currentState == LOW)
  {
    pressedTime = millis();
  }
  else if (lastState == LOW && currentState == HIGH)
  {
    releasedTime = millis();
    long pressDuration = releasedTime - pressedTime;
    if (pressDuration > 20)
    {
      if (ledControl == true)
      {
        data[0] = adress;
        data[1] = Enable_Tx;
        data[2] = Off;
        rs485_SoftUart.write(data, sizeof(data));
        memset(data, 0, sizeof(data));
        ledControl = false;
      }
      else if (ledControl == false)
      {
        data[0] = adress;
        data[1] = Enable_Tx;
        data[2] = On;
        rs485_SoftUart.write(data, sizeof(data));
        memset(data, 0, sizeof(data));
        ledControl = true;
      }
    }
  }
  lastState = currentState;
  while (rs485_SoftUart.available())
  {
    int lenRS = rs485_SoftUart.readBytes(dataRX, 3);

    if (dataRX[0] == adress)
    {
      if (dataRX[1] == Enable_Rx)
      {
        Serial.write(dataRX, 7);
        if (dataRX[2] == On)
        {
          data[0] = adress;
          data[1] = Enable_Tx;
          data[2] = On;
          ledControl = true;
        }
        else if (dataRX[2] == Off)
        {
          data[0] = adress;
          data[1] = Enable_Tx;
          data[2] = Off;
          ledControl = false;
        }
        rs485_SoftUart.write(data, sizeof(data));
        memset(data, 0, sizeof(data));
      }
    }
    memset(dataRX, 0, 3);
  }
  digitalWrite(LED, ledControl);
}