#include <Arduino.h>
#include <Keypad.h>
#include <LiquidCrystal_I2C.h>
#include <stdint.h>
#include <EEPROM.h>
extern volatile float target_pulse;

extern uint8_t currentStateCLK;
extern uint8_t lastStateCLK;
extern float newAngle;
extern uint8_t counterAngle;
extern char angleData[21][6];

extern bool checkPress;

extern float angleModeInput;
extern uint8_t numArrayInput;
extern bool checkEncoder;
/* SET UP SPEED */
extern char speedData[3];
extern uint16_t setupSpeed;
extern uint8_t numArraySpeed;
/* SET UP PULSE */
extern int pulse;
extern char pulseData[5];
extern uint8_t numArrayPulse;
/* SET UP PULSE */
extern float oneAngle;

typedef enum
{
    MODE_ENCOER,
    MODE_INPUT,
    MODE_AUTO,
    MODE_SETUP
} Mode_t;
extern Mode_t mode;

typedef enum
{
    MODEINSETUP_SPEED,
    MODEINSETUP_PULSE,
    MODEINSETUP_ONEANGLE,
} ModeInSetup_t;
extern ModeInSetup_t modeInSetup;
typedef struct
{
    bool isPressing;
    bool isLongDetected;
    bool currState;
    bool prevState;
    uint64_t pressTime;
    uint64_t releaseTime;
} Button_t;

void initSetup();
void initLcd();
void initInteruptTimer1();

void angleStep(float angleNew, float angleOld);

bool getPressKeyPad();
void getDataFromKeypad();

void getEncoder();
Mode_t checkButton(Button_t *bt, uint16_t buttonMode);

void initLcd();
void showLCD(Mode_t mode, float currAngle, uint8_t countAngle);
void showLcdEncoder(float angle);
void showLcdInput(uint8_t count);
void showLCDSetupSpeed();
void showLcdSetupPulse();
void showLcdSetupOneAngle();

void write_flash(const char *toStore, int startAddr);
String read_flash(int startAddr);
