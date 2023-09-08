#define IN1 7
#define IN2 6
#define IN3 5
#define IN4 4
#define MAX_SPEED 255
#define MIN_SPEED 0
int amthanh = 10;
int val = 0;
bool tt = 1;
void setup()
{
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  Serial.begin(9600);
  pinMode (amthanh, INPUT) ;
}

void motor_1_Dung() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
}

void motor_2_Dung() {
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
}

void motor_1_Tien(int speed) {
  speed = constrain(speed, MIN_SPEED, MAX_SPEED);
  digitalWrite(IN1, HIGH);
  analogWrite(IN2, 255 - speed);
}

void motor_1_Lui(int speed) {
  speed = constrain(speed, MIN_SPEED, MAX_SPEED);
  digitalWrite(IN1, LOW);
  analogWrite(IN2, speed);
}

void motor_2_Tien(int speed) {
  speed = constrain(speed, MIN_SPEED, MAX_SPEED);
  analogWrite(IN3, speed);
  digitalWrite(IN4, LOW);
}

void motor_2_Lui(int speed) {
  speed = constrain(speed, MIN_SPEED, MAX_SPEED);
  analogWrite(IN3, 255 - speed);
  digitalWrite(IN4, HIGH);
}

void loop()
{
  static unsigned long t_prev = 0;
  static int time_w = 0;
  if (digitalRead(amthanh) == 0) {
    delay(5);
    tt = !tt;
    while (digitalRead(amthanh) == 0) {
      delay(50);
    }
  }
  if (!tt) {
    if ( millis() - t_prev > 1000) {
      time_w++;
      t_prev = millis();
    }
    if (time_w <= 3) {
      Serial.println("di thang 1");
      motor_1_Tien(MAX_SPEED);
      motor_2_Tien(MAX_SPEED);
    }
    else if (time_w <= 4) {
      Serial.println("Queo");
      motor_1_Tien(MAX_SPEED);
      motor_2_Dung();
    }
    else if (time_w <= 6) {
      Serial.println("di thang 2");
      motor_1_Tien(MAX_SPEED);
      motor_2_Tien(MAX_SPEED);
    }
    else if (time_w > 6) {
      Serial.println("Dung !");
      time_w = 0;
      tt = 1;
    }
  }
  if (tt) {
    motor_1_Dung();
    motor_2_Dung();
  }
}
