
const unsigned int TRIG_PIN = 13;   // chan trig cam bien sieu am
const unsigned int ECHO_PIN = 12;   // cham echo cam bien sieu am 
#define TIME_OUT 5000               // cai thoi gian ngat khi cam bien ko hoat dong

#define led 3
int delay_time;         // khai bao bien luu gia tri delay 
float getDistance() {             // hma lay gia tri tu cam bien
  long duration, distanceCm;
  // gui xung den chan trig 
  digitalWrite(TRIG_PIN, LOW);        
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);
  // ngat gui xung
  duration = pulseIn(ECHO_PIN, HIGH, TIME_OUT);   // doc gia tri phan hoi tu cam bien
  distanceCm = duration / 29.1 / 2; // 29.1 toc do cam bien phan hoi | /2 chia doi quang duong -> khoang cach

  return distanceCm;
}

void setup() {
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
  pinMode(led, OUTPUT);
}

void loop() {
  static bool tt = 0;
  static long t_prev = 0, t_prev1 = 0;
  if (millis() - t_prev1 >= 1000) {
    long value = getDistance();
    t_prev1 = millis();
    if (value > 40) {       // neu khoang cach lon hon 40 den ko sang
      tt = 1;
    } else if (value < 40 && value > 30) {    // khoang cach tu 30-40 den sang 1s tat 1s
      delay_time = 1000;
      tt = 0;
    } else if (value < 30 && value > 20) {  // khoang cach tu 20-30 den sang 0.8s tat 0.8s
      delay_time = 800;
      tt = 0;
    } else if (value < 20 && value > 10) {  // khoang cach tu 10-20 den sang 0.6s tat 0.6s
      delay_time = 600;
      tt = 0;
    } else if (value < 10 && value > 5) { // khoang cach tu 5-10 den sang 0.4s tat 0.4s
      delay_time = 400;
      tt = 0;
    } else if (value < 5) {     // // khoang cach < 5 sang 0.1s tat 0.1s
      delay_time = 100;
      tt = 0;
    }
  }
  if (tt == 0) {            
    if (millis() - t_prev >= delay_time) {        // nhap nhay theo thoi gian "delay_time"
      digitalWrite(led, !digitalRead(led));       // toggle led
      t_prev = millis();
    }
  }
}
