#include <DS3231.h>
#include <SD.h>
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 20, 4);
DS3231 rtc(SDA, SCL);
Time t;

#define LED_VANG 4
#define LED_DO 5
#define LED_XANH 6

#define BT_UP 2
#define BT_DOWN 3
#define BT_NEXT 7

#define SHORT_PRESS_TIME 80

const char filename[] = "DATA.txt";

File txtFile;
typedef enum {
  RED,
  YELLOW,
  BLUE
} LED_COLOR_t;

typedef struct {
  int8_t dates;
  int8_t months;
} Date_t;
typedef struct {
  int8_t hours;
  int8_t minutes;
  int8_t seconds;
} Time_t;
typedef struct {
  Time_t time;
  Date_t date;
} DateTime_t;
DateTime_t datetime;
typedef struct {
  bool isPressing;
  bool isLongDetected;
  uint8_t LastState;
  uint8_t CurrentState;
  uint64_t PressedTime;
  uint64_t ReleasedTime;
  uint64_t LongDuring;
} Button_t;
Button_t ledR, ledB, ledY, btUp, btDown;
static unsigned long countLed = 0;
volatile unsigned long count = 0;
unsigned long countLeds, counts;
uint64_t timePressList;
bool checkPress = false;
bool checkPress_s = false;
void setup() {
  Serial.begin(115200);
  init_SD();
  lcd.init();
  lcd.backlight();
  rtc.begin();
  // rtc.setDOW(SUNDAY);         // Set Day-of-Week to SUNDAY
  // rtc.setTime(17, 45, 30);    // Set the t to 12:00:00 (24hr format)
  // rtc.setDate(22, 10, 2023);  // Set the date to January 1st, 2014
  init_LED();
  init_BT();
  lcd.clear();


  checkPress_s = checkPress;
  countLeds = 1;
  counts = 1;
}

void loop() {
  // Serial.println(digitalRead(LED_DO));
  t = rtc.getTime();
  detectLed(&ledY, LED_VANG);
  detectLed(&ledR, LED_DO);
  detectLed(&ledB, LED_XANH);

  button(&btUp, BT_UP);
  button(&btDown, BT_DOWN);
  if (checkPress_s != checkPress) {
    checkPress_s = checkPress;
    lcd.clear();
    if (checkPress == false) {
      showLCD();
    } else {
      showLCDPress(count);
    }
  }

  if (millis() - timePressList > 5000) {
    checkPress = false;
  }
  if (checkPress == false) {
    if (countLeds != countLed) {
      countLeds = countLed;
      showLCD();
    }
  } else if (checkPress == true) {
    if (counts != count) {
      counts = count;
      showLCDPress(count);
    }
  }
}
