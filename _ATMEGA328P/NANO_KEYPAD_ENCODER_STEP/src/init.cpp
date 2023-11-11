#include <init.h>
#define CLK 9
#define DT 10
#define SW 11

#define DIR A1
#define PUL A2
#define CTHT 12
extern uint8_t currentStateCLK;
extern uint8_t lastStateCLK;
extern LiquidCrystal_I2C lcd;

extern volatile bool goHome;
void initSetup()
{
    pinMode(CLK, INPUT);
    pinMode(DT, INPUT);
    pinMode(SW, INPUT);
    pinMode(CTHT, INPUT_PULLUP);
    pinMode(DIR, OUTPUT);
    pinMode(PUL, OUTPUT);

    initInteruptTimer1();

    lastStateCLK = digitalRead(CLK);
    for (int i = 0; i < sizeof(angleData) / 5; i++)
    {
        memset(angleData[i], '0', sizeof(angleData) / 5);
        angleData[i][3] = '.';
    }
    memset(speedData, '0', sizeof(speedData));
    sprintf(pulseData, "%d", pulse);

    String speedStr = read_flash(10);
    Serial.println(speedStr);
    String pulseStr = read_flash(40);
    Serial.println(pulseStr);
    String oneAngleStr = read_flash(80);
    Serial.println(oneAngleStr);

    setupSpeed = speedStr.toInt();
    pulse = pulseStr.toInt();
    oneAngle = oneAngleStr.toFloat();

    sprintf(speedData, "%d", setupSpeed);
    sprintf(pulseData, "%ld", pulse);

    // lcd.setCursor(0, 0);
    // lcd.print("GO HOME ...");
    // while (1)
    // {
    //     if (digitalRead(CTHT) == 0)
    //     {
    //         target_pulse = 0;
    //         break;
    //     }
    //     else
    //     {
    //         if (goHome == true)
    //         {
    //             goHome = false;
    //             target_pulse = 1600;
    //             initInteruptTimer1();
    //         }
    //     }
    // }
    mode = MODE_ENCOER;
    modeInSetup = MODEINSETUP_SPEED;
}