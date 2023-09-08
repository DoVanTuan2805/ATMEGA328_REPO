#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);

int flow;  //Water flow L/Min
int flowsensor = 2;
unsigned long currentTime;
unsigned long lastTime;
unsigned long pulse_freq;
String data_rx = "";
int maxs;
#define led_red 3
#define led_green 4
void pulse()  // Interrupt function
{
  pulse_freq++;
}

void setup() {
  lcd.init();
  lcd.backlight();
  pinMode(led_red, OUTPUT);
  pinMode(led_green, OUTPUT);
  pinMode(flowsensor, INPUT);
  Serial.begin(9600);
  attachInterrupt(0, pulse, FALLING);  // rising
  currentTime = millis();
  lastTime = currentTime;
}
bool check;
char buffer[5];
void loop() {
  sprintf(buffer, "%d ", flow);
  lcd.setCursor(0, 0);
  lcd.print("Water flow :");
  lcd.print(buffer);
  if (Serial.available()) {
    data_rx = Serial.readStringUntil('\n');
    maxs = data_rx.toInt();
  }
  currentTime = millis();
  if (currentTime >= (lastTime + 1000)) {
    lastTime = currentTime;
    flow = (pulse_freq / 7.5);
    pulse_freq = 0;  // Reset Counter
    Serial.println(flow);
  }
  check = check_data(flow, maxs);
  if (check == true) {
    lcd.setCursor(0, 1);
    lcd.print("Warnning !");
  } else if (check == false) {
    lcd.setCursor(0, 1);
    lcd.print("Normal !  ");
  }
}
bool check_data(double values, int max_v) {
  if (values >= max_v) {
    digitalWrite(led_red, HIGH);
    digitalWrite(led_green, LOW);
    return true;
  } else {
    digitalWrite(led_red, LOW);
    digitalWrite(led_green, HIGH);
    return false;
  }
}
