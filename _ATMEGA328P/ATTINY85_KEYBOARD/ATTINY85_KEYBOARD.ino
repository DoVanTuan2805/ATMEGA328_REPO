#include "DigiKeyboard.h"
#define up    0
#define down  1
#define right 2
#define left  3
#define right_1 4
#define left_2  5
void setup() {
  pinMode(0, INPUT);
  pinMode(1, INPUT);
  pinMode(2, INPUT);
  pinMode(3, INPUT);
  pinMode(4, INPUT);
  pinMode(5, INPUT);
}


void loop() {
  if (digitalRead(up) == HIGH) {
    DigiKeyboard.sendKeyStroke(82);
  }
  if (digitalRead(down) == HIGH) {
    DigiKeyboard.sendKeyStroke(81);
  }
  if (digitalRead(right) == HIGH) {
    DigiKeyboard.sendKeyStroke(79);
  }
  if (digitalRead(left) == HIGH) {
    DigiKeyboard.sendKeyStroke(80);
  }
  if (digitalRead(right_1) == HIGH) {
    DigiKeyboard.sendKeyStroke(89);
  }
  if (digitalRead(left_2) == HIGH) {
    DigiKeyboard.sendKeyStroke(30);
  }
}
