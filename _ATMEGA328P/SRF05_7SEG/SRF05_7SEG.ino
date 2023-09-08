#include <SoftwareSerial.h>
SoftwareSerial mySerial(A1, A0);  // RX, TX
const unsigned int TRIG_PIN = 13;
const unsigned int ECHO_PIN = 12;
#define TIME_OUT 5000
//ABCDEFG,dp
const int numeral[10] = {
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

//pins for decimal point and each segment
//dp, G, F, E, D, C, B, A
const int segmentPins[] = { 7, 9, 8, 6, 5, 4, 3, 2 };

const int numberofDigits = 1;

const int digitPins[numberofDigits] = { 3, 2, 1 };  //digits 1, 2, 3, 4

//int num[3];
int i = 0;
volatile long value = 0, value1;
int timer1_compare_match;
int num[3];
float getDistance() {
  long duration, distanceCm;

  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);

  duration = pulseIn(ECHO_PIN, HIGH, TIME_OUT);

  // convert to distance
  distanceCm = duration / 29.1 / 2;

  return distanceCm;
}

ISR(TIMER1_OVF_vect) {
  TCNT1 = timer1_compare_match;
  if (i == 3) {
    i = 0;
  } else {
    showDigit(num[i], i);
    i++;
  }
}
void showNumber(int number) {
  if (number == 0)
    showDigit(0, numberofDigits - 1);  //display 0 in the rightmost digit
  else {
    for (int digit = numberofDigits - 1; digit >= 0; digit--) {
      if (number > 0) {
        showDigit(number % 10, digit);
        number = number / 10;
      }
    }
  }
}

//Displays given number on a 7-segment display at the given digit position
void showDigit(int number, int digit) {
  num[0] = value / 100;
  num[1] = (value / 10) % 10;
  num[2] = value % 10;
  digitalWrite(digitPins[digit], HIGH);
  for (int segment = 1; segment < 8; segment++) {
    boolean isBitSet = bitRead(numeral[number], segment);
    isBitSet = !isBitSet;  //remove this line if common cathode display
    digitalWrite(segmentPins[segment], isBitSet);
  }
  delay(5);
  digitalWrite(digitPins[digit], LOW);
}

void setup() {
  mySerial.begin(9600);
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
  for (int i = 0; i < 8; i++) {
    pinMode(segmentPins[i], OUTPUT);  //set segment and DP pins to output
  }
  //sets the digit pins as outputs
  for (int i = 0; i < numberofDigits; i++) {
    pinMode(digitPins[i], OUTPUT);
  }
  noInterrupts();
  // Initialize Timer1
  timer1_compare_match = 65000;
  TCCR1A = 0;
  TCCR1B = 0;
  TIMSK1 = 0;
  /* Setup Timer/Counter1 */
  TCCR1B |= (1 << CS11) | (1 << CS10);  // prescale = 64
  TCNT1 = timer1_compare_match;
  TIMSK1 = (1 << TOIE1);
  interrupts();
}

void loop() {
  static long t_prev = 0;
  if (millis() - t_prev >= 1000) {
    value = getDistance();
    mySerial.println(value);
    t_prev = millis();
  }
  //showNumber(value);
}
