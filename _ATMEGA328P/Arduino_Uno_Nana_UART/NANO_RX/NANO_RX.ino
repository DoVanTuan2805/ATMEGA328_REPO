#include <SoftwareSerial.h>

const byte rx_Pin = 2;
const byte tx_Pin = 3;
int8_t x_availble;
SoftwareSerial my_serial_nano(rx_Pin, tx_Pin);

void setup() {
  pinMode(rx_Pin, INPUT);
  pinMode(tx_Pin, OUTPUT);
  my_serial_nano.begin(9600);
  Serial.begin(9600);
}
void loop() {
  if(my_serial_nano.available() > 0) {
    x_availble = my_serial_nano.read();
    Serial.print("Da nhan :");
    Serial.print(x_availble);
    Serial.println();
  }
}
