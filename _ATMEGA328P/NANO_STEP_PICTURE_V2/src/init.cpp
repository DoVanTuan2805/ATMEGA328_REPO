#include "init.h"

void initPinMode()
{
    pinMode(stepPin, OUTPUT);
    pinMode(dirPin, OUTPUT);

    pinMode(MS1, OUTPUT);
    pinMode(MS2, OUTPUT);
    pinMode(MS3, OUTPUT);

    digitalWrite(MS1, HIGH);
    digitalWrite(MS2, HIGH);
    digitalWrite(MS3, HIGH);

    pinMode(RL1, OUTPUT);
    pinMode(RL2, OUTPUT);

    pinMode(RUN, INPUT);
    pinMode(SET, INPUT);
    pinMode(UP, INPUT);
    pinMode(DOWN, INPUT);
    pinMode(CTHT, INPUT);
}