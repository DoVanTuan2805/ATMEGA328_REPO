int pwmOut = 6;
int i, value;
void setup() {
  pinMode(pwmOut, OUTPUT);
  pinMode(A0, INPUT);

}

void loop() {
  //  analogWrite(pwmOut, 0); // about zero volts
  //  delay(3000);
  // about 1 volt
  //  delay(3000);
  i = analogRead(A0);
  value = map (i , 0, 1023, 0, 255);
  analogWrite(pwmOut, value); // about 2 volts
  //  delay(3000);
  //  analogWrite(pwmOut, 128); // about 2.5 volts
  //  delay(3000);
  //  analogWrite(pwmOut, 153); // about 3.0 volts
  //  delay(3000);
  //  analogWrite(pwmOut, 204); // about 4.0 volts
  //  delay(3000);
  //  analogWrite(pwmOut, 255);  // about 5.0 volts
  //  delay(3000);

}
