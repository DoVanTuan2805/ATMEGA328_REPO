#include <init.h>

extern LiquidCrystal_I2C lcd;
#define CLK 9
#define DT 10
#define SW 11
#define SHORT_TIME 100
#define LONG_PRESS 1500
extern float oldAngle, oldAngleInput;

static float newAngle = 0;
static uint8_t counterAngle = 1;

static uint8_t currentStateCLK;
static uint8_t lastStateCLK;

static uint8_t modes = 1;
static uint8_t modeInSetups = 1;
extern char angleData[21][6];
static Mode_t mode;
static ModeInSetup_t modeInSetup;
extern bool checkEncoder;
static float oneAngle = 10.0;

void getEncoder()
{
    currentStateCLK = digitalRead(CLK);
    if (currentStateCLK != lastStateCLK && currentStateCLK == 1)
    {
        checkEncoder = true;
        // If the DT state is different than the CLK state then
        // the encoder is rotating CCW so decrement
        if (digitalRead(DT) != currentStateCLK)
        {
            // Encoder is rotating CW so increment
            if (mode == MODE_INPUT)
            {
                counterAngle++;
                if (counterAngle >= sizeof(angleData) / 6)
                {
                    counterAngle = 1;
                }
                numArrayInput = 0;
            }
            else if (mode == MODE_ENCOER)
            {
                newAngle += oneAngle;
                if (newAngle >= 360)
                {
                    newAngle = 360;
                }
            }
            else if (mode == MODE_SETUP)
            {
                modeInSetups--;

                if (modeInSetups <= 1)
                {
                    modeInSetups = 3;
                }
                switch (modeInSetups)
                {
                case 1:
                    modeInSetup = MODEINSETUP_SPEED;
                    break;
                case 2:
                    modeInSetup = MODEINSETUP_PULSE;
                    break;
                case 3:
                    modeInSetup = MODEINSETUP_ONEANGLE;
                    break;
                default:
                    break;
                }
            }
        }
        else
        {
            if (mode == MODE_INPUT)
            {
                counterAngle--;
                if (counterAngle < 1)
                {
                    counterAngle = sizeof(angleData) / 6 - 1;
                }
                numArrayInput = 0;
            }
            else if (mode == MODE_ENCOER)
            {
                newAngle -= oneAngle;
                if (newAngle <= -360)
                {
                    newAngle = -360;
                }
            }
            else if (mode == MODE_SETUP)
            {
                modeInSetups++;

                if (modeInSetups >= 4)
                {
                    modeInSetups = 1;
                }
                switch (modeInSetups)
                {
                case 1:
                    modeInSetup = MODEINSETUP_SPEED;
                    break;
                case 2:
                    modeInSetup = MODEINSETUP_PULSE;
                    break;
                case 3:
                    modeInSetup = MODEINSETUP_ONEANGLE;
                    break;
                default:
                    break;
                }
            }
        }
    }
    else
    {
        checkEncoder = false;
    }
    // Remember last CLK state
    lastStateCLK = currentStateCLK;
}
Mode_t checkButton(Button_t *bt, uint16_t buttonMode)
{
    bt->currState = digitalRead(buttonMode);

    if (bt->prevState == HIGH && bt->currState == LOW) // press
    {
        Serial.println("Press");
        bt->pressTime = millis();
        bt->isPressing = true;
        bt->isLongDetected = false;
    }
    else if (bt->prevState == LOW && bt->currState == HIGH) // release
    {
        Serial.println("Release");
        bt->releaseTime = millis();
        bt->isPressing = false;

        if (bt->releaseTime - bt->pressTime > SHORT_TIME)
        {
            if (buttonMode == SW)
            {
                modes++;
                if (modes > 1)
                {
                    modes = 0;
                }
                switch (modes)
                {
                case 0:
                    mode = MODE_ENCOER;
                    oldAngle = angleModeInput;
                    newAngle = oldAngleInput;
                    break;
                case 1:
                    mode = MODE_INPUT;
                    oldAngleInput = newAngle;
                    angleModeInput = oldAngleInput;
                    break;
                case 2:
                    // mode = MODE_AUTO;
                    break;
                default:
                    break;
                }
                lcd.clear();
            }
        }
        if (bt->releaseTime - bt->pressTime > LONG_PRESS)
        {
            lcd.noBlink();
            lcd.clear();
            if (mode != MODE_SETUP)
            {
                mode = MODE_SETUP;
                modeInSetup = MODEINSETUP_SPEED;
            }
        }

        Serial.println(mode);
    }

    bt->prevState = bt->currState;
    return mode;
}