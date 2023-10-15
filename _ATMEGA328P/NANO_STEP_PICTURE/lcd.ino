void mainLcd(bool page, uint8_t mode) {
  char dataLine1[16];
  char dataLine2[16];
  if (page == 0) {
    if (mode == 0) {
      sprintf(dataLine1, "Distance:  >%d  ", Distance);
      lcd.setCursor(0, 0);
      lcd.print(dataLine1);
      memset(dataLine1, 0, sizeof(dataLine1));
      sprintf(dataLine2, "NOP:        %d  ", NOP);
      lcd.setCursor(0, 1);
      lcd.print(dataLine2);
      memset(dataLine2, 0, sizeof(dataLine2));
    } else if (mode == 1) {
      sprintf(dataLine1, "Distance:   %d  ", Distance);
      lcd.setCursor(0, 0);
      lcd.print(dataLine1);
      memset(dataLine1, 0, sizeof(dataLine1));
      sprintf(dataLine2, "NOP:       >%d  ", NOP);
      lcd.setCursor(0, 1);
      lcd.print(dataLine2);
      memset(dataLine2, 0, sizeof(dataLine2));
    } else if (mode == 2) {
      sprintf(dataLine1, "NOP:       %d  ", NOP);
      lcd.setCursor(0, 0);
      lcd.print(dataLine1);
      memset(dataLine1, 0, sizeof(dataLine1));
      sprintf(dataLine2, "SPEED:   > ", speed);
      lcd.setCursor(0, 1);
      lcd.print(dataLine2);
      lcd.print(speed);
    } else if (mode == 3) {
      sprintf(dataLine1, "SPEED:     ", speed);
      lcd.setCursor(0, 0);
      lcd.print(dataLine1);
      lcd.print(speed);
      memset(dataLine1, 0, sizeof(dataLine1));
      sprintf(dataLine2, "S_Pic:    >%d  ", speedPicture);
      lcd.setCursor(0, 1);
      lcd.print(dataLine2);
    }

  } else {
    if (goHomeComplete == false) {
      sprintf(dataLine1, " START     STOP  ");
      lcd.setCursor(0, 0);
      lcd.print(dataLine1);
      memset(dataLine1, 0, sizeof(dataLine1));

      sprintf(dataLine2, "TO HOME    BACK  ");
      lcd.setCursor(0, 1);
      lcd.print(dataLine2);
      memset(dataLine2, 0, sizeof(dataLine2));
    } else {
      sprintf(dataLine1, " START    STOP  ");
      lcd.setCursor(0, 0);
      lcd.print(dataLine1);
      memset(dataLine1, 0, sizeof(dataLine1));

      sprintf(dataLine2, " RUN      BACK ");
      lcd.setCursor(0, 1);
      lcd.print(dataLine2);
      memset(dataLine2, 0, sizeof(dataLine2));
    }
  }
}
void processLCD() {
  char dataLine1[16];
  char dataLine2[16];
  sprintf(dataLine1, "Running...");
  lcd.setCursor(0, 0);
  lcd.print(dataLine1);
  memset(dataLine1, 0, sizeof(dataLine1));

  sprintf(dataLine2, "NOP:        %d  ", NOP);
  sprintf(dataLine2, "NOP: %d   /%d   ", NOP_process, NOP);
  lcd.setCursor(0, 1);
  lcd.print(dataLine2);
  memset(dataLine2, 0, sizeof(dataLine2));
}