#include "init.h"
#include "default.h"
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 16, 2);

extern float speed;
extern uint16_t speedPicture;
extern uint16_t Distance;
extern uint16_t NOP;

static ModeMain_t modeMain;
static ModeSetup_t modeSetup;
char dataLine1[16], dataLine2[16];
void initLCD()
{
    lcd.init();
    lcd.backlight();
    lcd.clear();
    modeMain = MODE_MAIN;
    modeSetup = MODE_SPEED;
    showLCD(modeMain, modeSetup);
}
void showLCD(ModeMain_t modeMainLCD, ModeSetup_t modeSetupLCD)
{
    if (modeMainLCD == MODE_MAIN)
    {
        if (modeSetupLCD == MODE_DISTANCE)
        {
            showModeDistance();
        }
        else if (modeSetupLCD == MODE_NOS)
        {
            showModeNOS();
        }
        else if (modeSetupLCD == MODE_SPEED)
        {
            showModeSpeed();
        }
        else if (modeSetupLCD == MODE_TIME_SHOT)
        {
            showModeTimeShot();
        }
    }
    else if (modeMainLCD == MODE_GOHOME)
    {
    }
    else if (modeMainLCD == MODE_RUN)
    {
    }
}
void showModeDistance()
{
    sprintf(dataLine1, "Distance:  >%d  ", Distance);
    lcd.setCursor(0, 0);
    lcd.print(dataLine1);
    memset(dataLine1, 0, sizeof(dataLine1));
    sprintf(dataLine2, "NOS:        %d  ", NOP);
    lcd.setCursor(0, 1);
    lcd.print(dataLine2);
    memset(dataLine2, 0, sizeof(dataLine2));
}
void showModeNOS()
{
    sprintf(dataLine1, "Distance:   %d  ", Distance);
    lcd.setCursor(0, 0);
    lcd.print(dataLine1);
    memset(dataLine1, 0, sizeof(dataLine1));
    sprintf(dataLine2, "NOS:       >%d  ", NOP);
    lcd.setCursor(0, 1);
    lcd.print(dataLine2);
    memset(dataLine2, 0, sizeof(dataLine2));
}
void showModeSpeed()
{
    sprintf(dataLine1, "NOS:       %d  ", NOP);
    lcd.setCursor(0, 0);
    lcd.print(dataLine1);
    memset(dataLine1, 0, sizeof(dataLine1));
    sprintf(dataLine2, "SPEED:   > ", speed);
    lcd.setCursor(0, 1);
    lcd.print(dataLine2);
    lcd.print(speed);
}
void showModeTimeShot()
{
    sprintf(dataLine1, "SPEED:     ", speed);
    lcd.setCursor(0, 0);
    lcd.print(dataLine1);
    lcd.print(speed);
    memset(dataLine1, 0, sizeof(dataLine1));
    sprintf(dataLine2, "S_Pic:    >%d  ", speedPicture);
    lcd.setCursor(0, 1);
    lcd.print(dataLine2);
}
