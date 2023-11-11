#include <init.h>

extern LiquidCrystal_I2C lcd;
#define rows 4
#define columns 3

extern Mode_t mode;
extern uint8_t counterAngle;

char keys[rows][columns] = {
    {'1', '2', '3'},
    {'4', '5', '6'},
    {'7', '8', '9'},
    {'.', '0', '#'},
};
/* MODE : INPUT DATA ANGLE*/
static char angleData[21][6];
static uint8_t numArrayInput = 0;

/* MODE : SETUP ->  SPEED*/
static char speedData[3];
static uint8_t numArraySpeed = 0;
extern uint16_t setupSpeed;

/* MODE : SETUP ->  PULSE*/
static char pulseData[6];
static uint8_t numArrayPulse = 0;
extern uint64_t pulse;

/* MODE : SETUP ->  ONE ANGLE*/
extern float oneAngle;

byte rowPins[rows] = {8, 7, 6, 5};
byte columnPins[columns] = {4, 3, 2};
Keypad keypad = Keypad(makeKeymap(keys), rowPins, columnPins, rows, columns);

static float angleModeInput;
char key = 0;
bool checkPress;

extern ModeInSetup_t modeInSetup;

bool getPressKeyPad(char *data)
{
    char temp = keypad.getKey();
    if ((int)keypad.getState() == PRESSED)
    {
        if (temp != 0)
        {
            key = temp;
            Serial.println(key);
            checkPress = true;
            return checkPress;
        }
    }
    checkPress = false;
    return checkPress;
}
void getDataFromKeypad()
{
    static bool checkData;
    static uint8_t counterAngles;
    if (mode == MODE_INPUT)
    {
        checkData = getPressKeyPad(&key);
        if (checkData != false)
        {
            if (counterAngles != counterAngle)
            {
                numArrayInput = 0;
                counterAngles = counterAngle;
            }
            if (key != '#')
            {

                if (numArrayInput < 5)
                {
                    if (numArrayInput == 0)
                    {
                        if (key == '.')
                        {
                            angleData[counterAngle][numArrayInput++] = '-';
                        }
                        else
                        {
                            angleData[counterAngle][numArrayInput++] = key;
                        }
                    }
                    else
                    {
                        angleData[counterAngle][numArrayInput++] = key;
                    }
                }
                else if (numArrayInput >= 5)
                {
                    numArrayInput = 0;
                    angleData[counterAngle][numArrayInput++] = key;
                }
            }
            else
            {
                angleData[counterAngle][5] = '\0';
                String s = String(angleData[counterAngle]);
                angleModeInput = s.toFloat();
                Serial.println(angleModeInput);
            }
        }
    }
    else if (mode == MODE_SETUP)
    {
        checkData = getPressKeyPad(&key);
        if (checkData != false)
        {
            if (modeInSetup == MODEINSETUP_SPEED)
            {
                if ((key != '#') && (key != '.'))
                {

                    if (numArraySpeed < 3)
                    {
                        speedData[numArraySpeed++] = key;
                    }
                    else if (numArraySpeed >= 3)
                    {
                        numArraySpeed = 0;
                        speedData[numArraySpeed++] = key;
                    }
                }
                else if (key == '#')
                {
                    speedData[3] = '\0';
                    // write eeprom
                    write_flash(speedData, 10);
                    String s = String(speedData);

                    setupSpeed = s.toInt();
                    if (setupSpeed > 525)
                    {
                        setupSpeed = 525;
                    }
                    Serial.printf("SPEED : %d\n", setupSpeed);
                }
            }
            else if (modeInSetup == MODEINSETUP_PULSE)
            {
                if ((key != '#') && (key != '.'))
                {
                    if (numArrayPulse < 6)
                    {
                        pulseData[numArrayPulse++] = key;
                    }
                    else if (numArrayPulse >= 6)
                    {
                        numArrayPulse = 0;
                        pulseData[numArrayPulse++] = key;
                    }
                }
                else if (key == '#')
                {
                    pulseData[6] = '\0';
                    // write eeprom
                    write_flash(pulseData, 40);

                    String s = String(pulseData);

                    pulse = s.toInt();
                    Serial.print("PULSE");
                    
                    Serial.print(s);
                    Serial.println();
                }
            }
            else if (modeInSetup == MODEINSETUP_ONEANGLE)
            {
                if (key == '1')
                {
                    oneAngle = 0.1;
                }
                else if (key == '2')
                {
                    oneAngle = 1.0;
                }
                else if (key == '3')
                {
                    oneAngle = 10.0;
                }
                String s1 = String(oneAngle);
                // write eeprom
                write_flash(s1.c_str(), 80);
            }
        }
    }
}
