void checkButton(Button_t *bt, uint16_t buttonMode) {
  bt->currState = digitalRead(buttonMode);

  if (bt->prevState == HIGH && bt->currState == LOW)  // press
  {
    //Serial.println("Press");
    if (buttonMode == CTHT) {
      Serial.println("Press CTHT");
      interrupt_soft = 1;
    }
    bt->pressTime = millis();
    bt->isPressing = true;
    bt->isShortDetected = false;
  } else if (bt->prevState == LOW && bt->currState == HIGH)  // release
  {
    //Serial.println("Release");
    if (buttonMode == CTHT) {
      Serial.println("Realse CTHT");
      interrupt_soft = 0;
    }
    bt->releaseTime = millis();
    bt->isPressing = false;

    if (bt->releaseTime - bt->pressTime > SHORT_TIME) {
      Serial.println("Detect button");
      if (buttonMode == SET) {
        runningBack = true;
        if (page == 0) {
          if (mode < 3) {
            mode++;
          } else {
            mode = 0;
          }
        }
        if (page == 1) {
          page = 0;
          goHome = false;
          goHomeComplete = false;
        }
      }
      if (buttonMode == RUN) {
        if (page == 0) {
          page = 1;
          goHome = false;
        } else if (page == 1) {
          if (goHomeComplete == false) {
            goHome = true;
          } else {
            running = true;
          }
        }
      }
    }
  }
  if (bt->isPressing == true) {
    if (millis() - bt->pressTime > SHORT_TIME) {
      if (buttonMode == UP) {
        if (mode == 0) {
          if (Distance < 400) {
            Distance++;
          }
        }
        if (mode == 1) {
          NOP++;
        }
        if (mode == 2) {
          if (speed < 1) {
            speed += 0.1;
          }
        }
        if (mode == 3) {
          if (speedPicture < 3000) {
            speedPicture += 100;
          }
        }
      }
      if (buttonMode == DOWN) {
        if (mode == 0) {
          if (Distance > 1) {
            Distance--;
          }
        }
        if (mode == 1) {
          if (NOP > 10) {
            NOP--;
          }
        }
        if (mode == 2) {
          if (speed > 0.2) {
            speed -= 0.1;
          }
        }
        if (mode == 3) {
          if (speedPicture > 100) {
            speedPicture -= 100;
          }
        }
      }
    }
  }
  bt->prevState = bt->currState;
}