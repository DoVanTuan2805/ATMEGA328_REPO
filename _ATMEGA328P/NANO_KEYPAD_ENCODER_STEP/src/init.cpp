#include <init.h>
#define CLK 9
#define DT 10
#define SW 11

#define DIR A1
#define PUL A2

extern uint8_t currentStateCLK;
extern uint8_t lastStateCLK;

void initSetup()
{
    pinMode(CLK, INPUT);
    pinMode(DT, INPUT);
    pinMode(SW, INPUT);

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
}