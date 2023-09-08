#include <SoftwareSerial.h>
const byte rx_Pin = 3;
const byte tx_Pin = 2;
SoftwareSerial my_serial_uno(rx_Pin, tx_Pin);

int8_t x = 10;

struct data_tx
{
  char name[20];
  int tuoi;
};

void setup() {
  pinMode(rx_Pin, INPUT);
  pinMode(tx_Pin, OUTPUT);
  my_serial_uno.begin(9600);
  Serial.begin(9600);
}

void loop() {
  data_tx data1, data2;
  struct data_tx data3, data4;
  
  my_serial_uno.write(x);
  Serial.print("Da gui : ");
  Serial.print(x);
  Serial.println();
  delay(1000);
}
