#include <init.h>
void setup()
{
  Serial.begin(9600);
  initPinMode();
  initLCD();
  initButton();
}

void loop()
{
}
