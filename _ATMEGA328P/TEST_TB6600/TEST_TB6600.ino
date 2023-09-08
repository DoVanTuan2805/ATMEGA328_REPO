#define DIR_PIN 6
#define STEP_PIN 7
#define EN_PIN 5

void setup() {
  Serial.begin(9600);
  pinMode(DIR_PIN, OUTPUT);
  pinMode(STEP_PIN, OUTPUT);
  pinMode(EN_PIN, OUTPUT);
  pinMode(EN_PIN, HIGH);
}
int value;
bool data_in;
void loop() {
  if (Serial.available() > 0) {
    value = Serial.parseInt();
    data_in = 1;
  }
  if (data_in == 1) {
    Serial.println(value);
    pinMode(EN_PIN, LOW);
    rotateDeg(value, 0.5);
    pinMode(EN_PIN, HIGH);
    data_in = 0;
  }
}



void rotate(int steps, float speed) {
  //rotate a specific number of microsteps (8 microsteps per step) - (negitive for reverse movement)
  //speed is any number from .01 -> 1 with 1 being fastest - Slower is stronger
  int dir = (steps > 0) ? HIGH : LOW;
  steps = abs(steps);

  digitalWrite(DIR_PIN, dir);

  float usDelay = (1 / speed) * 70;

  for (int i = 0; i < steps; i++) {
    digitalWrite(STEP_PIN, HIGH);
    delayMicroseconds(usDelay);

    digitalWrite(STEP_PIN, LOW);
    delayMicroseconds(usDelay);
  }
}

void rotateDeg(float deg, float speed) {
  //rotate a specific number of degrees (negitive for reverse movement)
  //speed is any number from .01 -> 1 with 1 being fastest - Slower is stronger
  int dir = (deg > 0) ? HIGH : LOW;
  digitalWrite(DIR_PIN, dir);

  int steps = abs(deg) * (1 / 0.225);
  float usDelay = (1 / speed) * 70;

  for (int i = 0; i < steps; i++) {
    digitalWrite(STEP_PIN, HIGH);
    delayMicroseconds(usDelay);

    digitalWrite(STEP_PIN, LOW);
    delayMicroseconds(usDelay);
  }
}