#ifndef INIT_H
#define INIT_H

#include <Arduino.h>
#include "button.h"
#include <stdint.h>

#define MS1 2
#define MS2 3
#define MS3 4

#define stepPin 5
#define dirPin 6

#define RL1 11
#define RL2 12

#define RUN 7
#define SET 8
#define UP 9
#define DOWN 10
#define CTHT A1

#define SHORT_TIME 50

#define ONE_MM 335
typedef enum
{
    MODE_MAIN,
    MODE_GOHOME,
    MODE_RUN,
} ModeMain_t;
typedef enum
{
    MODE_DISTANCE,
    MODE_NOS,
    MODE_SPEED,
    MODE_TIME_SHOT
} ModeSetup_t;

extern Button_t BTrun, BTset, BTup, BTdown, BTctht;

void initPinMode();

void initLCD();
void showLCD(ModeMain_t modeMainLCD, ModeSetup_t modeSetupLCD);
void showModeDistance();
void showModeNOS();
void showModeSpeed();
void showModeTimeShot();

void initButton();

#endif