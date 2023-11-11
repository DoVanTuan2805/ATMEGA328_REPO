#ifndef BUTTON_H
#define BUTTON_H

#include <Arduino.h>
#include "init.h"
#include <stdint.h>

typedef struct
{
    uint8_t btn_filter;
    uint8_t btn_last;
    uint8_t btn_current;
    uint8_t is_press;
    uint16_t pressTimeOut;
    uint16_t PIN;
    uint32_t t_debounce;
    uint32_t time_start_press;
} Button_t;

void Button_Init(Button_t *button, uint16_t PIN, uint16_t timeOut = 2000);
void bt_handle(Button_t *button);
static void bt_press_callback(Button_t *button);
static void bt_release_callback(Button_t *button);
static void bt_press_timout_callback(Button_t *button);
#endif