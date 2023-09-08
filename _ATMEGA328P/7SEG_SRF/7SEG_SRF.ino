long value = 0;
 // khai bao led 7 doan (dp, G, F, E, D, C, B, A)
const int segmentPins[] = { 7, 9, 8, 6, 5, 4, 3, 2 };    
const int numeral[10] = {         // khai bao trang thai bit cho tung so
  B11111100,  //0
  B01100000,  //1
  B11011010,  //2
  B11110010,  //3
  B01100110,  //4
  B10110110,  //5
  B00111110,  //6
  B11100000,  //7
  B11111110,  //8
  B11100110,  //9
};
const unsigned int TRIG_PIN = 13;   // chan trig cam bien sieu am
const unsigned int ECHO_PIN = 12;   // cham echo cam bien sieu am 
#define TIME_OUT 5000               // cai thoi gian ngat khi cam bien ko hoat dong
int num;
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
void showNum (int number){        // quet led theo tung bit duoc khai bao o "numeral"
  for (int segment = 1; segment < 8; segment++) {
    boolean isBitSet = bitRead(numeral[number], segment);
    isBitSet = !isBitSet;  //remove this line if common cathode display
    digitalWrite(segmentPins[segment], isBitSet);
  }
}
void setup() {
  Serial.begin(9600);
  pinMode(TRIG_PIN, OUTPUT);    
  pinMode(ECHO_PIN, INPUT);
  for (int i = 0; i < 8; i++) {     // khai bao chan chuc nang OUTPUT
    pinMode(segmentPins[i], OUTPUT);  //set segment and DP pins to output
  }
}

void loop() {
  static long t_prev = 0;
  if (millis() - t_prev >= 500) {   // moi 500ms se thuc hien 1 lan
    value = getDistance();        // luu gia tri doc tu cam bien vao value
    num = value / 10;
    Serial.println(num);
    showNum(num);                 // hien thi len led 7 doan
    t_prev = millis();
  }
}
