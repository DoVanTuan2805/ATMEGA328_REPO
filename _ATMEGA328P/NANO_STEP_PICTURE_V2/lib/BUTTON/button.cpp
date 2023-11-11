#include "button.h"

static Button_t run, set, up, down, ctht;

void initButton()
{
    Button_Init(&BTset, SET);
    Button_Init(&BTrun, RUN);
    Button_Init(&BTup, UP);
    Button_Init(&BTdown, DOWN);
    Button_Init(&BTctht, CTHT);
}
// ----------------- FUNCTION ---------------
static void bt_press_callback(Button_t *button)
{
    if (button->PIN == CTHT)
    {
    }
}
static void bt_release_callback(Button_t *button)
{
    if (button->PIN == SET)
    {
    }
    else if (button->PIN == RUN)
    {
    }
    else if (button->PIN == UP)
    {
    }
    else if (button->PIN == DOWN)
    {
    }
}
static void bt_press_timout_callback(Button_t *button)
{
}
void bt_handle(Button_t *button)
{ // GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin
    uint8_t state = digitalRead(button->PIN);
    if (state != button->btn_filter)
    { /// loc nhieu nut nhan
        button->btn_filter = state;
        button->t_debounce = millis();
    }
    if (millis() - button->t_debounce >= 15)
    { /// het khoang thoi gian nhieu
        button->btn_current = state;
        if (button->btn_current != button->btn_last)
        { // dang nhan
            if (button->btn_current == 0)
            {
                button->time_start_press = millis();
                button->is_press = 1;
                bt_press_callback(button);
            }
            else
            {
                bt_release_callback(button);
            }
            button->btn_last = button->btn_current;
        }
    }
    if (button->is_press && millis() - button->time_start_press >= button->pressTimeOut)
    {
        button->is_press = 0;
        bt_press_timout_callback(button);
    }
}
void Button_Init(Button_t *button, uint16_t PIN, uint16_t timeOut = 2000)
{
    button->PIN = PIN;
    button->btn_filter = 1;
    button->btn_last = 1;
    button->btn_current = 0;
    button->t_debounce = 0;
    button->time_start_press = 0;
    button->is_press = 0;
    button->pressTimeOut = timeOut;
}
