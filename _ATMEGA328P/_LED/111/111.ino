#include <Wire.h>
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0X27, 16, 2);  //SCL A5 SDA A4
#define led1 1
#define led2 2
#define led3 3
#define led4 4
#define led5 5
#define led6 8

const int btA = 6;
const int btD = 7;

bool lastButtonState = 0;
unsigned long buttonPressTime = 0;
unsigned int timeHold = 3000;
int mode = 5;
int modes = 1;
int stD = 0;
int delay_mode1 = 100;
int delay_mode2 = 100;
int delay_mode3 = 100;
int delay_mode4 = 100;
int delay_mode5 = 100;
bool stateBTA = 1;
bool stateBTD = 1;
bool tt = 0;
int count = 0;
int counts = 0;
#define l1(x) digitalWrite(led1, x)
#define l2(x) digitalWrite(led2, x)
#define l3(x) digitalWrite(led3, x)
#define l4(x) digitalWrite(led4, x)
#define l5(x) digitalWrite(led5, x)
#define l6(x) digitalWrite(led6, x)
void setup() {
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  pinMode(led3, OUTPUT);
  pinMode(led4, OUTPUT);
  pinMode(led5, OUTPUT);
  pinMode(led6, OUTPUT);

  pinMode(btA, INPUT);
  pinMode(btD, INPUT);

  lcd.init();
  lcd.backlight();
}

void loop() {
  stateBTA = digitalRead(btA);
  stateBTD = digitalRead(btD);
  lcd.setCursor(2, 1);
  lcd.print(mode);
  lcd.setCursor(4, 1);
  lcd.print(tt);
  lcd.setCursor(6, 1);
  lcd.print(count);

  if (digitalRead(btD) == 0) {
    while (digitalRead(btD) == 0) {
      counts++;
      stD = 1;
      count = counts;
      lcd.setCursor(10, 1);
      lcd.print(counts);
      delay(100);
      lcd.clear();
    }
    counts = 0;
  }

  if (count < 10 && count > 1) {
    count = 0;
    tt = !tt;
    l6(1);
    delay(1000);
    l6(0);
  }
  if (tt == 0) {
    mode = 5;
  }
  if (tt == 1) {
    mode = 1;
  }

  switch (mode) {
    case 1:
      cd1(stateBTA);
      break;
    case 2:
      cd2(stateBTA);
      break;
    case 3:
      cd3(stateBTA);
      break;
    case 4:
      cd4(stateBTA);
      break;
    case 5:
      cd5(stateBTA);
      break;
  }
}
void cd1(bool stt) {
  if (stt == 1) {
    l1(0);
  } else {
    l1(1);
    delay(delay_mode1);
    l1(0);
    delay(delay_mode1);
    l2(1);
    delay(delay_mode1);
    l2(0);
    delay(delay_mode1);
    l3(1);
    delay(delay_mode1);
    l3(0);
    delay(delay_mode1);
    l4(1);
    delay(delay_mode1);
    l4(0);
    delay(delay_mode1);
  }
}
void cd2(bool stt) {
  int dl1 = random(50, 1000);
  int dl2 = random(50, 1000);
  if (stt == 1) {
    l2(0);
  } else {
    l2(1);
    delay(dl1);
    l2(0);
    delay(dl2);
  }
}
void cd3(bool stt) {
  if (stt == 1) {
    l3(0);
  } else {
    l3(1);
    //l4(1);
    delay(100);
    l3(0);
    //l4(0);
    delay(100);
  }
}
void cd4(bool stt) {
  if (stt == 1) {
    l4(0);
  } else {
    for (int i = 0; i < 5; i++) {
      l4(1);
      delay(delay_mode3);
      l4(0);
      delay(delay_mode3);
    }
    delay(1000);
    for (int i = 0; i < 5; i++) {
      l4(1);
      delay(delay_mode3);
      l4(0);
      delay(delay_mode3);
    }
    for (int i = 0; i < 5; i++) {
      l4(1);
      delay(delay_mode3);
      l4(0);
      delay(delay_mode3);
    }
  }
}
void cd5(bool stt) {
  if (stt == 1) {
    l5(0);
  } else {
    l5(1);
  }
}
