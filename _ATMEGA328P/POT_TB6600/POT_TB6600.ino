#define DIR_PIN 6
#define STEP_PIN 5

void setup() {
  Serial.begin(9600);
  pinMode(A0, INPUT);
  pinMode(DIR_PIN, OUTPUT);
  pinMode(STEP_PIN, OUTPUT);
}

void loop() {
  double value = map(analogRead(A0), 1023, 0, 0, 10);
  Serial.print(analogRead(A0));
  Serial.print("----");
  Serial.println(value);
  rotateDeg(360, value);
}
void rotateDeg(float deg, float speed) {
  int dir = (deg > 0) ? HIGH : LOW;
  digitalWrite(DIR_PIN, dir);

  int steps = abs(deg) * (1 / 0.225);  //0.225
  float usDelay = (1 / (speed / 10)) * 70;

  for (int i = 0; i < steps; i++) {
    digitalWrite(STEP_PIN, HIGH);
    delayMicroseconds(usDelay);

    digitalWrite(STEP_PIN, LOW);
    delayMicroseconds(usDelay);
  }
}