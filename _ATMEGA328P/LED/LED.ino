#include <Wire.h>
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0X27, 16, 2);  //SCL A5 SDA A4
#define led1 1
#define led2 2
#define led3 3
#define led4 4
#define led5 5

const int btA = 6;
const int btB = 7;
const int btC = 8;
int mode = 1;

int delay_mode1 = 100;
int delay_mode2 = 100;
int delay_mode3 = 100;
int delay_mode4 = 100;
int delay_mode5 = 100;
bool stateBTA = 1;
bool stateBTB = 1;
bool stateBTC = 1;
bool staC = 1;
#define l1(x) digitalWrite(led1, x)
#define l2(x) digitalWrite(led2, x)
#define l3(x) digitalWrite(led3, x)
#define l4(x) digitalWrite(led4, x)
#define l5(x) digitalWrite(led5, x)
void setup() {
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  pinMode(led3, OUTPUT);
  pinMode(led4, OUTPUT);
  pinMode(led5, OUTPUT);

  pinMode(btA, INPUT);
  pinMode(btB, INPUT);

  lcd.init();
  lcd.backlight();
}

void loop() {
  stateBTA = digitalRead(btA);
  if (digitalRead(btC) == 0) {
    delay(5);
    staC = !staC;
    while (digitalRead(btC) == 0)
      delay(5);
  }
  if (staC == 1) {
    if (digitalRead(btB) == 0) {
      delay(5);
      mode++;
      if (mode > 4) {
        mode = 1;
      }
      while (digitalRead(btB) == 0)
        delay(5);
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
    }
  }
  if (staC == 0) {
    cd5(stateBTA);
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
    for (int i = 0; i < 3; i++) {
      l3(1);
      delay(delay_mode3);
      l3(0);
      delay(delay_mode3);
    }
    delay(1000);
    for (int i = 0; i < 4; i++) {
      l3(1);
      delay(delay_mode3);
      l3(0);
      delay(delay_mode3);
    }
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
