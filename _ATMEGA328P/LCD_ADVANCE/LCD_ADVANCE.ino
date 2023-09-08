#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 20, 4);
#define up 36
#define down 39
#define select 34
int option = 1;
bool choose = 0;
void setup() {
  pinMode(up, INPUT);
  pinMode(down, INPUT);
  pinMode(select, INPUT);
  lcd.init();
  lcd.backlight();
  //lcd.createChar(1, degree);
}

void loop() {
  if (digitalRead(up) == 0) {
    delay(50);
    option++;
    if (option > 4) {
      option = 1;
    }
    lcd.clear();
    while (digitalRead(up) == 0)
      delay(50);
  }
  if (digitalRead(down) == 0) {
    delay(50);
    option--;
    if (option < 1) {
      option = 4;
    }
    lcd.clear();
    while (digitalRead(down) == 0)
      delay(50);
  }
  if (digitalRead(select) == 0) {
    delay(50);
    choose = !choose;
    lcd.clear();
    while (digitalRead(select) == 0)
      delay(50);
  }
  if (choose == 0) {
    switch (option) {
      case 1: main_1(); break;
      case 2: main_2(); break;
      case 3: main_3(); break;
      case 4: main_4(); break;
    }
  } else {
    switch (option) {
      case 1: select_1(); break;
      case 2: select_2(); break;
      case 3: select_3(); break;
      case 4: select_4(); break;
    }
  }
}
void main_1() {
  lcd.setCursor(0, 0);
  lcd.print("> OPTION 1");
  lcd.setCursor(0, 1);
  lcd.print("  OPTION 2");
  lcd.setCursor(0, 2);
  lcd.print("  OPTION 3");
  lcd.setCursor(0, 3);
  lcd.print("  OPTION 4");
}

void main_2() {
  lcd.setCursor(0, 0);
  lcd.print("  OPTION 1");
  lcd.setCursor(0, 1);
  lcd.print("> OPTION 2");
  lcd.setCursor(0, 2);
  lcd.print("  OPTION 3");
  lcd.setCursor(0, 3);
  lcd.print("  OPTION 4");
}
void main_3() {
  lcd.setCursor(0, 0);
  lcd.print("  OPTION 1");
  lcd.setCursor(0, 1);
  lcd.print("  OPTION 2");
  lcd.setCursor(0, 2);
  lcd.print("> OPTION 3");
  lcd.setCursor(0, 3);
  lcd.print("  OPTION 4");
}
void main_4() {
  lcd.setCursor(0, 0);
  lcd.print("  OPTION 1");
  lcd.setCursor(0, 1);
  lcd.print("  OPTION 2");
  lcd.setCursor(0, 2);
  lcd.print("  OPTION 3");
  lcd.setCursor(0, 3);
  lcd.print("> OPTION 4");
}
void select_1() {
  lcd.setCursor(0, 0);
  lcd.print("MAIN OPTION 1");
}
void select_2() {
  lcd.setCursor(0, 0);
  lcd.print("MAIN OPTION 2");
}
void select_3() {
  lcd.setCursor(0, 0);
  lcd.print("MAIN OPTION 3");
}
void select_4() {
  lcd.setCursor(0, 0);
  lcd.print("MAIN OPTION 4");
}