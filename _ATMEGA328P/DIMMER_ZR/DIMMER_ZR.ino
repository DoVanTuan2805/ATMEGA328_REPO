int LAMP = 6;
int dim_val = 0;
void setup() {
  Serial.begin(9600);
  pinMode(LAMP, OUTPUT);
  attachInterrupt(digitalPinToInterrupt(2), zero_cross, CHANGE);
}
void zero_cross() {
  // int dimming_time = (20 * dim_val);
  int dimming_time = dim_val;
  delayMicroseconds(dimming_time);
  digitalWrite(LAMP, HIGH);
  delayMicroseconds(100);
  digitalWrite(LAMP, LOW);
}
int data = 0;
void loop() {
  data += 5;
  if (data >= 1023) {
    data = 0;
  }
  Serial.println(data);
  // int data = analogRead(A0);
  // int data1 = map(data, 0, 1023, 850, 1100);
  int data1 = map(data, 0, 1023, 0, 4500);
  // Serial.println(data1);
  dim_val = data1;
  delay(200);
}
