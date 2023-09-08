#include <LiquidCrystal_I2C.h>
#include <DallasTemperature.h>
#include <OneWire.h>
#include <SoftwareSerial.h>

SoftwareSerial mySerial(11, 12);  // RX, TX

#define ONE_WIRE_BUS A0

// LCD pins
#define SDA A4
#define SCL A5
//LED, buzzer
#define LED_ALARM 3
#define LED_NORMAL 4
#define buzzer A3


// Setup a oneWire instance to communicate with any OneWire devices
OneWire oneWire(ONE_WIRE_BUS);

// Pass our oneWire reference to Dallas Temperature.
DallasTemperature DS18B20(&oneWire);

LiquidCrystal_I2C lcd(0x27, 16, 2);  // The I2C address may be different in your project, see the notes below.

float tempC = 29.39;
float previousTemp;
float tempAlarm = 36;
float tempMin = 30;
float temp = 0.1;
unsigned long prev_time = 0;
String data;
float temp_max, temp_min;
void setup() {
  mySerial.begin(9600);
  Serial.begin(9600);
  pinMode(LED_ALARM, OUTPUT);
  pinMode(LED_NORMAL, OUTPUT);
  pinMode(buzzer, OUTPUT);

  digitalWrite(LED_ALARM, HIGH);
  digitalWrite(LED_NORMAL, HIGH);
  delay(500);
  digitalWrite(LED_ALARM, LOW);
  digitalWrite(LED_NORMAL, LOW);
  digitalWrite(buzzer, LOW);
  lcd.init();
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print(" Canh bao nhiet ");
  lcd.setCursor(0, 1);
  lcd.print("Cam bien DS18B20");

  DS18B20.begin();

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Nhiet do: ");

  lcd.setCursor(0, 1);
  lcd.print("Nhiet bao: ");
  lcd.setCursor(14, 1);
  lcd.print(tempAlarm);
  //delay(5000);
}

float getTemperature() {
  float temp_C;
  DS18B20.requestTemperatures();
  temp_C = DS18B20.getTempCByIndex(0);
  while (temp_C == (-127.0));
  return temp_C;
}

void checkTemp(int temp_curr, int temp_max) {
  if (temp_curr > temp_max) {
    //Serial.println("Temp overload");
    digitalWrite(LED_ALARM, HIGH);
    digitalWrite(buzzer, HIGH);
    digitalWrite(LED_NORMAL, LOW);

  } else if (temp_curr <= temp_max) {
    //Serial.println("Temp in range");
    digitalWrite(LED_ALARM, LOW);
    digitalWrite(buzzer, LOW);
    digitalWrite(LED_NORMAL, HIGH);
  }
}
String tach_chuoi(String text, String ki_tu, uint16_t vi_tri) {
  String tmp = text;
  for (int i = 0 ; i < vi_tri; i++) {
    tmp = tmp.substring(tmp.indexOf(ki_tu) + 1);
    if (tmp.indexOf(ki_tu) == -1 && i != vi_tri - 1) {       // neu ko tim thay ki tu (delim)tra ve -1
      return "";
    }
  }
  return tmp.substring(0, tmp.indexOf(ki_tu));
}
void loop() {
  
  //tempC = getTemperature();
  while (Serial.available() > 0) {
    data = Serial.readStringUntil('\n');
    temp_min = (tach_chuoi(data,"/", 0)).toFloat();
    temp_max = (tach_chuoi(data,"/", 1)).toFloat();
    mySerial.println(temp_min);
    mySerial.println(temp_max);
    data = "";
  }
  if (millis() - prev_time > 500) {
    prev_time = millis();
    tempC = tempC + temp;
    Serial.println(tempC);
  }
  if (tempC != previousTemp) {
    lcd.setCursor(11, 0);
    lcd.print(tempC);
    previousTemp = tempC;
  }
}
