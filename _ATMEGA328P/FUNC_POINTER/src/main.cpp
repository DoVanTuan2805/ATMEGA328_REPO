#include <Arduino.h>
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 16, 2);
#define NUM_OF_SCREEN 4
typedef enum
{
  SCREEN1 = 0,
  SCREEN2 = 1,
  SCREEN3 = 2,
  SCREEN4 = 3,
} Screen_t;
int ArrayScreen(Screen_t screen, int a, int b);
int screen1(int a, int b);
int screen2(int a, int b);
int screen3(int a, int b);
int screen4(int a, int b);

static int (*handleScreen[NUM_OF_SCREEN])(int a, int b){
    [SCREEN1] = screen1,
    [SCREEN2] = screen2,
    [SCREEN3] = screen3,
    [SCREEN4] = screen4,
};

void setup()
{
  Serial.begin(9600);
  lcd.init();
  lcd.backlight();
  lcd.clear();
}

void loop()
{
  ArrayScreen(SCREEN1, 1, 2);
}
int ArrayScreen(Screen_t screen, int a, int b)
{
  if ((*handleScreen[screen] != NULL) && (screen < NUM_OF_SCREEN))
  {
    return handleScreen[screen](a, b);
  }
  else
  {
    Serial.println("ERROR !");
  }
}
int screen1(int a, int b)
{
  lcd.setCursor(0, 0);
  lcd.print("screen 1");
}
int screen2(int a, int b)
{
  lcd.setCursor(0, 0);
  lcd.print("screen 2");
}
int screen3(int a, int b)
{
  lcd.setCursor(0, 0);
  lcd.print("screen 3");
}
int screen4(int a, int b)
{
  lcd.setCursor(0, 0);
  lcd.print("screen 4");
}