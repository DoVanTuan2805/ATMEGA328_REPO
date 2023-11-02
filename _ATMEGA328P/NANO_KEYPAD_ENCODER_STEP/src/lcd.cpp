#include <init.h>
LiquidCrystal_I2C lcd(0x27, 16, 2);
extern uint8_t counterAngle;
extern uint8_t numArrayInput;
extern uint8_t numArraySpeed;
extern uint8_t numArrayPulse;

extern ModeInSetup_t modeInSetup;

void initLcd()
{
    lcd.init(); // initialize the lcd
    lcd.backlight();
}
void showLcdEncoder(float angle)
{
    lcd.setCursor(0, 0);
    lcd.print("MODE: QUAY TAY");

    lcd.setCursor(0, 1);
    lcd.print("GOC : ");
    lcd.print(angle);
    lcd.print("   ");
    lcd.noBlink();
}
void showLcdInput(uint8_t count)
{
    char data[5];
    uint8_t positionX;
    lcd.setCursor(0, 0);
    lcd.print("MODE: NHAP DL ");

    lcd.setCursor(0, 1);
    lcd.printf("GOC %d : ", count);
    sprintf(data, "%c%c%c%c%c", angleData[count][0], angleData[count][1], angleData[count][2], angleData[count][3], angleData[count][4]);
    lcd.print(data);
    lcd.print(" ");
    if (count < 10)
    {
        positionX = 8 + numArrayInput;
        lcd.setCursor(positionX, 1);
        lcd.blink();
    }
    else
    {
        positionX = 9 + numArrayInput;
        lcd.setCursor(positionX, 1);
        lcd.blink();
    }
}
void showLCDSetupSpeed()
{
    char data[4];
    uint8_t pos;
    lcd.setCursor(0, 0);
    lcd.print("MODE: CAI DAT ");

    lcd.setCursor(0, 1);
    sprintf(data, "%c%c%c", speedData[0], speedData[1], speedData[2]);
    lcd.print("TOC DO : ");
    lcd.print(data);

    pos = 9 + numArraySpeed;
    lcd.setCursor(pos, 1);
    lcd.blink();
    memset(data, 0, sizeof(data));
}
void showLcdSetupPulse()
{
    char data[4];
    uint8_t pos;
    lcd.setCursor(0, 0);
    lcd.print("MODE: CAI DAT ");

    lcd.setCursor(0, 1);
    sprintf(data, "%c%c%c%c%c ", pulseData[0], pulseData[1], pulseData[2], pulseData[3], pulseData[4]);
    lcd.print("XUNG : ");
    lcd.print(data);

    pos = 7 + numArrayPulse;
    lcd.setCursor(pos, 1);
    lcd.blink();
    memset(data, 0, sizeof(data));
}
void showLcdSetupOneAngle()
{
    lcd.setCursor(0, 0);
    lcd.print("MODE: CAI DAT ");

    lcd.setCursor(0, 1);
    lcd.print("1 GOC : ");
    lcd.print(oneAngle);
}
void showLCD(Mode_t mode, float currAngle, uint8_t countAngle)
{
    switch (mode)
    {
    case MODE_ENCOER:
        showLcdEncoder(currAngle);
        break;
    case MODE_INPUT:
        showLcdInput(countAngle);
        break;
    case MODE_AUTO:
        break;
    case MODE_SETUP:
        if (modeInSetup == MODEINSETUP_SPEED)
        {
            showLCDSetupSpeed();
        }
        else if (modeInSetup == MODEINSETUP_PULSE)
        {
            showLcdSetupPulse();
        }
        else if (modeInSetup == MODEINSETUP_ONEANGLE)
        {
            showLcdSetupOneAngle();
        }

        break;
    default:
        break;
    }
}
