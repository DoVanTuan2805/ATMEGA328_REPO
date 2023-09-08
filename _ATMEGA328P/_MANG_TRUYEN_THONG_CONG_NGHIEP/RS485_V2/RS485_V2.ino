#include <SoftwareSerial.h>

#define RS485RX 4 // Serial Receive pin
#define RS485TX 3 // Serial Transmit pin

#define LED 13
#define BUTTON 2
SoftwareSerial RS485(RS485RX, RS485TX); // RX, TX
char byteReceived[4];
byte SlaveAdress = 0x02;

byte Rx = 0x03;
byte Tx = 0x04;

byte EnableOnOff = 0x05; // ON OFF
byte EnableValue = 0x06; // float value

byte On = 0x01;
byte Off = 0x00;

bool onOff;


int value;
byte data[7];

uint64_t prev;
bool stateButton;

void ngat_isr()
{
  if (stateButton == true)
  {
    data[0] = SlaveAdress;
    data[1] = Tx;
    data[2] = EnableOnOff;
    data[3] = Off;
    RS485.write(data, sizeof(data));
    memset(data, 0, sizeof(data));
    stateButton = false;
  }
  else if (stateButton == false)
  {
    data[0] = SlaveAdress;
    data[1] = Tx;
    data[2] = EnableOnOff;
    data[3] = On;
    RS485.write(data, sizeof(data));
    memset(data, 0, sizeof(data));
    stateButton = true;
  }
}
void setup()
{
  Serial.begin(9600);
  pinMode(LED, OUTPUT);
  pinMode(BUTTON, INPUT_PULLUP);
  attachInterrupt(0, ngat_isr, FALLING);
  RS485.begin(9600);
}

void loop()
{
  while (RS485.available()) // tìm dữ liệu từ thiết bị khác truyền về
  {
    int lenRS = RS485.readBytes(byteReceived, 4); // đọc byte nhận được
    Serial.write(byteReceived, lenRS);
    if (byteReceived[0] == SlaveAdress)
    {
      if (byteReceived[1] == Rx)
      {
        if (byteReceived[2] == EnableOnOff)
        {
          if (byteReceived[3] == On)
          {
            data[0] = SlaveAdress;
            data[1] = Tx;
            data[2] = EnableOnOff;
            data[3] = On;
            RS485.write(data, 4);
            memset(data, 0, sizeof(data));
            stateButton = true;
          }
          else if (byteReceived[3] == Off)
          {
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