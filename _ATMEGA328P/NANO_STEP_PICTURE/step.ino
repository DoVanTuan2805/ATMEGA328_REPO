void rotate_CTHT(int steps, float speed) {
  //rotate a specific number of microsteps (8 microsteps per step) - (negitive for reverse movement)
  //speed is any number from .01 -> 1 with 1 being fastest - Slower is stronger`
  steps = abs(steps);
  float usDelay = (1 / speed) * 70;

  for (int i = 0; i < steps; i++) {
    checkButton(&ctht, CTHT);
    if (interrupt_soft == 1) {
      break;
    }
    digitalWrite(stepPin, HIGH);
    delayMicroseconds(usDelay);

    digitalWrite(stepPin, LOW);
    delayMicroseconds(usDelay);
  }
}
void rotate_Picture(int steps, float speed) {
  steps = abs(steps);
  float usDelay = (1 / speed) * 70;

  for (int i = 0; i < steps; i++) {
    checkButton(&set, SET);
    if (runningBack == true) {
      runningBack = false;
      goHomeComplete = false;
      running = false;
      page = 0;
      mode = 0;
      break;
    }
    digitalWrite(stepPin, HIGH);
    delayMicroseconds(usDelay);

    digitalWrite(stepPin, LOW);
    delayMicroseconds(usDelay);
  }
  timeRelay = millis();
  takePictureComplete = false;
}
