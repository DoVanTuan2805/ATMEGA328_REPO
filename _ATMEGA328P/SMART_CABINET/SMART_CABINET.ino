#include <Wire.h>
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 16, 2);

const int cash = 2;  //connect blue wire to pin 15, purple to ground
uint8_t pulse;
uint8_t money = 0;
uint8_t counter = 0;


typedef enum {
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

void setup() {
  Serial.begin(9600);
  pinMode(cash, INPUT_PULLUP);
  Serial.println("Cash machine booted");
  lcd.init();
  lcd.backlight();
}
void loop() {
}
void getMoney() {
  if (digitalRead(cash) == 0) {
    pulse = pulseIn(cash, LOW);
    Serial.println(pulse);
    if (pulse > 70) {
      Serial.println("Bill Accepted!");
      money = money + 1;
      Serial.print("money :");
      Serial.println(money);
      pulse = 0;
    }
    // Serial.println(pulse);
  } else if (digitalRead(cash) == 1) {
  }
}
