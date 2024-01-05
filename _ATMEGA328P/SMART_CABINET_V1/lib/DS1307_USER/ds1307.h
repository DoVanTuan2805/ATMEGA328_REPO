#ifndef _DS1307_USER_H
#define _DS1307_USER_H
#include <Wire.h>
#include <stdio.h>

typedef struct
{
    uint8_t second;
    uint8_t minute;
    uint8_t hour;
    uint8_t day;
    uint8_t wday;
    uint8_t month;
    uint16_t year;
} DateTime_t;

void readDS1307();
int bcd2dec(uint8_t num);
int dec2bcd(uint8_t num);
void setTime(uint8_t hr, uint8_t min, uint8_t sec, uint8_t wd, uint8_t d, uint8_t mth, uint8_t yr);
#endif