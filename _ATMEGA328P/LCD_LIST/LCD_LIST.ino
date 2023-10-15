#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include "RTClib.h"

#define UP 7
#define DOWN 8
#define MODE 9
#define CTHT A1
RTC_DS1307 rtc;
LiquidCrystal_I2C lcd(0x27, 16, 2);
#define SHORT_PRESS_TIME 1000
typedef struct {
  uint8_t LastState;
  uint8_t CurrentState;
  uint64_t PressedTime;
  uint64_t ReleasedTime;
  uint64_t LongDuring;
} Button_t;
Button_t btUp, btDown, btMode, btCTHT;
typedef struct {
  int8_t hour;
  int8_t minute;
  int8_t second;
} DateTime_t;
DateTime_t getDateTime[255];
uint8_t count = 0, countShow = 2;
bool mode = 0;
DateTime now;
void getEvent() {
  getDateTime[count].hour = now.hour();
  getDateTime[count].minute = now.minute();
  getDateTime[count].second = now.second();
  count++;
}

void setup() {
  Serial.begin(9600);
  pinMode(UP, INPUT);
  pinMode(DOWN, INPUT);
  pinMode(MODE, INPUT);
  pinMode(CTHT, INPUT);
  lcd.init();
  lcd.backlight();
  if (!rtc.begin()) {
    while (1)
      ;
  }

  if (!rtc.isrunning()) {
  }

  rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
  // attachInterrupt(0, getEvent, RISING);
}
void loop() {
  now = rtc.now();
  button(&btUp, UP);
  button(&btDown, DOWN);
  button(&btMode, MODE);
  button(&btCTHT, CTHT);
  if (mode == 0) {
    if (count >= 2) {
      lcdShow(count - 2, count - 1);
    } else {
      lcdShow(0, 1);
    }
  } else {
    lcdShow(countShow - 2, countShow - 1);
  }
}
void lcdShow(uint8_t i, uint8_t j) {
  char dataLine1[16];
  sprintf(dataLine1, "%d- %2d : %2d : %2d", i, getDateTime[i].hour, getDateTime[i].minute, getDateTime[i].second);
  lcd.setCursor(0, 0);
  lcd.print(dataLine1);
  memset(dataLine1, 0, sizeof(dataLine1));

  char dataLine2[16];
  sprintf(dataLine2, "%d- %2d : %2d : %2d", j, getDateTime[j].hour, getDateTime[j].minute, getDateTime[j].second);
  lcd.setCursor(0, 1);
  lcd.print(dataLine2);
  memset(dataLine2, 0, sizeof(dataLine2));
}
void button(Button_t *bt, uint16_t buttonPin) {
  bt->CurrentState = digitalRead(buttonPin);

  if (bt->LastState == HIGH && bt->CurrentState == LOW)  // button is pressed
    bt->PressedTime = millis();
  else if (bt->LastState == LOW && bt->CurrentState == HIGH) {  // button is released
    bt->ReleasedTime = millis();

    bt->LongDuring = bt->ReleasedTime - bt->PressedTime;
    if (bt->LongDuring < SHORT_PRESS_TIME) {
      if (mode == 1) {
        if (buttonPin == UP) {
          Serial.println("up");
          if (count < 255) {
            countShow++;
          }
        }
        if (buttonPin == DOWN) {
          Serial.println("down");
          if (count > 0) {
            countShow--;
          }
        }
      }
      if (buttonPin == CTHT) {
        getEvent();
      }
      if (buttonPin == MODE) {
        Serial.println("mode");
        lcd.clear();
        if (mode == 1) {
          mode = 0;
        } else {
          mode = 1;
        }
      }
    }
  }
  bt->LastState = bt->CurrentState;
}