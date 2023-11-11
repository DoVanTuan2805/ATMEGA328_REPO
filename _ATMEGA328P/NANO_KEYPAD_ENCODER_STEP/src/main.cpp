#include <Arduino.h>
#include <init.h>

#define SW 11

float oldAngle, oldAngleInput;
uint8_t angleCounts;
Button_t btEncoder;
Mode_t modeMain, modeMains;
uint64_t time;
bool checkKeyPad, checkEncoder;

void setup()
{
  Serial.begin(9600);
  initLcd();
  initSetup();

  Serial.println("START");
  // angleStep(-360);
  oldAngle = 0;
  newAngle = 0;
  oldAngleInput = 0;
  modeMain = MODE_ENCOER;
  showLCD(modeMain, newAngle, counterAngle);
  btEncoder.currState = digitalRead(SW);
  btEncoder.prevState = digitalRead(SW);
}

void loop()
{
  modeMain = checkButton(&btEncoder, SW);
  getEncoder();
  if (mode == MODE_ENCOER)
  {
    if (oldAngle != newAngle)
    {
      angleStep(newAngle, oldAngle);
      oldAngle = newAngle;
    }
  }
  else if (mode == MODE_INPUT)
  {
    getDataFromKeypad();
    if (oldAngleInput != angleModeInput)
    {
      angleStep(angleModeInput, oldAngleInput);
      oldAngleInput = angleModeInput;
    }
  }
  else if (mode == MODE_SETUP)
  {
    getDataFromKeypad();
  }

  // if (oldAngle != newAngle || modeMains != modeMain || angleCounts != counterAngle || checkKeyPad != checkPress)
  // {
  //   showLCD(modeMain, newAngle, counterAngle);
  //   checkKeyPad = checkPress;
  //   angleCounts = counterAngle;
  //   modeMains = modeMain;
  //   oldAngle = newAngle;
  // }
  if (checkEncoder == true || checkKeyPad != checkPress || modeMains != modeMain)
  {
    // Serial.println(oneAngle);
    showLCD(modeMain, newAngle, counterAngle);
    modeMains = modeMain;
    checkKeyPad = checkPress;
  }
}