void showLCD() {
  char buffLine0[17], buffLine1[17], buffLine2[17], buffLine3[17];
  char buffCount0[5], buffCount1[5], buffCount2[5], buffCount3[5];
  memset(buffLine0, 0, sizeof(buffLine0));
  memset(buffLine1, 0, sizeof(buffLine1));
  memset(buffLine2, 0, sizeof(buffLine2));
  memset(buffLine3, 0, sizeof(buffLine3));
  if (countLed == 0) {
    sprintf(buffLine0, "dd/mm hh:ss XX");
    sprintf(buffLine1, "dd/mm hh:ss XX");
    sprintf(buffLine2, "dd/mm hh:ss XX");
    sprintf(buffLine3, "dd/mm hh:ss XX");
  } else if (countLed == 1) {
    readDataSD(buffLine0, countLed - 1);
    sprintf(buffLine1, "dd/mm hh:ss XX");
    sprintf(buffLine2, "dd/mm hh:ss XX");
    sprintf(buffLine3, "dd/mm hh:ss XX");
  } else if (countLed == 2) {
    readDataSD(buffLine0, countLed - 1);
    readDataSD(buffLine1, countLed - 2);
    sprintf(buffLine2, "dd/mm hh:ss XX");
    sprintf(buffLine3, "dd/mm hh:ss XX");
  } else if (countLed == 3) {
    readDataSD(buffLine0, countLed - 1);
    readDataSD(buffLine1, countLed - 2);
    readDataSD(buffLine2, countLed - 3);
    sprintf(buffLine3, "dd/mm hh:ss XX");
  } else if (countLed >= 4) {
    readDataSD(buffLine0, countLed - 1);
    readDataSD(buffLine1, countLed - 2);
    readDataSD(buffLine2, countLed - 3);
    readDataSD(buffLine3, countLed - 4);
  }
  // ADD NUM RED BLUE YELLOW TOTAL
  sprintf(buffCount0, "%d", numRED);
  sprintf(buffCount1, "%d", numYELLOW);
  sprintf(buffCount2, "%d", numBLUE);
  sprintf(buffCount3, "%d", total);

  lcd.setCursor(0, 0);
  lcd.print(buffLine0);
  lcd.setCursor(17, 0);
  lcd.print(buffCount0);

  lcd.setCursor(0, 1);
  lcd.print(buffLine1);
  lcd.setCursor(17, 1);
  lcd.print(buffCount1);

  lcd.setCursor(0, 2);
  lcd.print(buffLine2);
  lcd.setCursor(17, 2);
  lcd.print(buffCount2);

  lcd.setCursor(0, 3);
  lcd.print(buffLine3);
  lcd.setCursor(17, 3);
  lcd.print(buffCount3);



  // Serial.print("buffLine1 : ");
  // Serial.print(buffLine1);
  // Serial.println();

  // Serial.print("buffLine2 : ");
  // Serial.print(buffLine2);
  // Serial.println();

  // Serial.print("buffLine3 : ");
  // Serial.print(buffLine3);
  // Serial.println();
}
void showLCDPress(int line) {
  char buffLine0[17], buffLine1[17], buffLine2[17], buffLine3[17];
  memset(buffLine0, 0, sizeof(buffLine0));
  memset(buffLine1, 0, sizeof(buffLine1));
  memset(buffLine2, 0, sizeof(buffLine2));
  memset(buffLine3, 0, sizeof(buffLine3));

  readDataSD(buffLine0, line);
  readDataSD(buffLine1, line - 1);
  readDataSD(buffLine2, line - 2);
  readDataSD(buffLine3, line - 3);

  lcd.setCursor(0, 0);
  lcd.print(buffLine0);

  lcd.setCursor(0, 1);
  lcd.print(buffLine1);

  lcd.setCursor(0, 2);
  lcd.print(buffLine2);

  lcd.setCursor(0, 3);
  lcd.print(buffLine3);

  // Serial.print("buffLine0 : ");
  // Serial.print(buffLine0);
  // Serial.println();

  // Serial.print("buffLine1 : ");
  // Serial.print(buffLine1);
  // Serial.println();

  // Serial.print("buffLine2 : ");
  // Serial.print(buffLine2);
  // Serial.println();

  // Serial.print("buffLine3 : ");
  // Serial.print(buffLine3);
  // Serial.println();
}
