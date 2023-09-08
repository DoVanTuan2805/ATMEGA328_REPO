#include <SoftwareSerial.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 16, 2);
SoftwareSerial mySerial(12, 11);  // RX, TX
#define DO        9
#define AO        A1
#define LED_GREEN 3
#define LED_RED   5
#define BUZ       4
unsigned int sensorValue = 650, flameDetect = 0;
unsigned int curr_time, prev_time;
String data_tx = "", data_rx, tt_waring, set_value;
bool tt = 0, tt_buz = 1;
void setup() {
  Serial.begin(9600);
  mySerial.begin(9600);
  pinMode(DO, INPUT);
  pinMode(AO, INPUT);
  pinMode(LED_GREEN, OUTPUT);
  pinMode(LED_RED, OUTPUT);
  pinMode(BUZ, OUTPUT);
  lcd.init();
  lcd.backlight();
  mySerial.println("Begin !!!");
}

void loop() {
  flameDetect = digitalRead(DO);
  sensorValue = analogRead(AO);
  if (Serial.available() > 0) {
    data_rx = Serial.readStringUntil('\n');
    data_rx.trim();
    tt_waring = getValue(data_rx , '/', 0);
    set_value = getValue(data_rx , '/', 1);
  }
  curr_time = millis();
  if (curr_time - prev_time > 200) {
    lcd.clear();
    prev_time = curr_time;
    data_tx = data_tx + flameDetect + "/" + sensorValue;
    Serial.println(data_tx);
    data_tx = "";
    int set_values = set_value.toInt();
    check_warning(tt_waring, set_values);
  }
}
void check_warning(String tt_w, int value_w) {
  if (sensorValue >= value_w) {
    if (tt_w == "False") {
      digitalWrite(BUZ, !digitalRead(BUZ));
      lcd.setCursor(5, 0);
      lcd.print("Flame Detect");
      mySerial.println("Flame Detect");
    }
    else {
      digitalWrite(BUZ, LOW);
      lcd.setCursor(5, 0);
      lcd.print("Flame Not Detect");
      mySerial.println("Flame Not Detect");
    }
  }
  else {
    digitalWrite(BUZ, LOW);
    lcd.setCursor(5, 0);
    lcd.print("Flame Not Detect");
    mySerial.println("Flame Not Detect");
  }
}
String getValue(String data, char separator, int index) {
  int found = 0;
  int strIndex[] = { 0, -1 };
  int maxIndex = data.length() - 1;
  for (int i = 0; i <= maxIndex && found <= index; i++) {
    if (data.charAt(i) == separator || i == maxIndex) { //data.charAt(i) xuất ra kí tự ở vị trí (i)
      found++;
      strIndex[0] = strIndex[1] + 1;
      strIndex[1] = (i == maxIndex) ? i + 1 : i;
      // (i == maxIndex) true -> i + 1
      // (i == maxIndex) false -> i
    }
  }
  return found > index ? data.substring( strIndex[0], strIndex[1] ) : "";
}
