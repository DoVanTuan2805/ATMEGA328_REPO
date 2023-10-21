uint16_t numRED, numBLUE, numYELLOW;
uint16_t total;

void getDateTime() {
  datetime.time.hours = t.hour;
  datetime.time.minutes = t.min;
  datetime.time.seconds = t.sec;

  datetime.date.dates = t.date;
  datetime.date.months = t.mon;
}
void detectLed(Button_t *led, uint16_t ledPin) {
  LED_COLOR_t ledColor;
  led->CurrentState = digitalRead(ledPin);
  if (led->LastState == HIGH && led->CurrentState == LOW) {  // button is pressed
    led->PressedTime = millis();
    led->isPressing = true;
    led->isLongDetected = false;
    getDateTime();
  } else if (led->LastState == LOW && led->CurrentState == HIGH) {  // button is released
    led->ReleasedTime = millis();
    led->isPressing = false;
  }
  if (led->isPressing == true && led->isLongDetected == false) {
    led->LongDuring = millis() - led->PressedTime;
    if (led->LongDuring > SHORT_PRESS_TIME) {
      if (ledPin == LED_VANG) {
        ledColor = YELLOW;
        numYELLOW++;
      } else if (ledPin == LED_DO) {
        ledColor = RED;
        numRED++;
      } else if (ledPin == LED_XANH) {
        numBLUE++;
        ledColor = BLUE;
      }
      total = numYELLOW + numRED + numBLUE;

      writeDataSD(datetime.date.dates, datetime.date.months, datetime.time.hours, datetime.time.minutes, datetime.time.seconds, ledColor);
      led->isLongDetected = true;
    }
  }
  led->LastState = led->CurrentState;
}

void button(Button_t *bt, uint16_t buttonPin) {
  bt->CurrentState = digitalRead(buttonPin);

  if (bt->LastState == HIGH && bt->CurrentState == LOW) {  // button is pressed
    bt->PressedTime = millis();
  } else if (bt->LastState == LOW && bt->CurrentState == HIGH) {  // button is released
    bt->ReleasedTime = millis();

    bt->LongDuring = bt->ReleasedTime - bt->PressedTime;

    if (bt->LongDuring > 100 && bt->LongDuring < 1000) {

      if (buttonPin == BT_UP) {
        Serial.println("Press Up");
        if (count < countLed) {
          count++;
        }
      }
      if (buttonPin == BT_DOWN) {
        Serial.println("Press Down");
        if (count > 3) {
          count--;
        }
      }
      if (buttonPin == BT_NEXT) {
        Serial.println("Press Next");
        if (mode > 4) {
          mode = 0;
        } else {
          mode++;
        }
        switch (mode) {
          case 0:
            menu = MAIN;
            break;
          case 1:
            menu = MAIN_1;
            break;
          case 2:
            menu = MENU_YELLOW;
            break;
          case 3:
            menu = MENU_BLUE;
            break;
          case 4:
            menu = MENU_RED;
            break;
        }
      }
      Serial.println(count);
      checkPress = true;
      timePressList = millis();
    }
  }
  bt->LastState = bt->CurrentState;
}