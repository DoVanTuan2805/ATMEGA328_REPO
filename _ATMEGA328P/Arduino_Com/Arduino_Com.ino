String a;
void setup() {
  Serial.begin(9600);

}

void loop() {
  // Serial.println("Hello");
  // delay(1000);
  if(Serial.available())
  {
    a = Serial.readString();
    Serial.println(a);
  }
}
