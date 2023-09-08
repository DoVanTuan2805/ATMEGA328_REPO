#include "avr/interrupt.h"
#define DIR_PIN 6
#define STEP_PIN 7
#define EN_PIN 5

int8_t dir_step;
volatile int counter_timer;
volatile int step;
int counter_top, counter_bot;
int16_t vong;
volatile int soxung;
ISR(TIMER2_COMPA_vect) {
  if (dir_step != 0) {
    if()
    counter_timer++;
    if (counter_timer <= counter_top) {
      digitalWrite(STEP_PIN, HIGH);
    }
    if (counter_timer > counter_top) {
      digitalWrite(STEP_PIN, LOW);
    }
    if (counter_timer > counter_bot) {
      soxung++;
      counter_timer = 0;
      if (dir_step > 0) step++;
      else if (dir_step < 0) step--;
    }
  }
}
void setup() {
  Serial.begin(9600);
  pinMode(DIR_PIN, OUTPUT);
  pinMode(STEP_PIN, OUTPUT);
  pinMode(EN_PIN, OUTPUT);

  // TIMER 2 : 8 BIT
  TCCR2A = 0;
  TCCR2B = 0;

  TCCR2B |= (1 << CS21);  // PRESACLER 8
  // 16MHZ / 8 = 2MHZ  => 1 NHIP DEM 0.5us
  OCR2A = 39;              // 0.5us * 40 = 20us
  TCCR2A |= (1 << WGM21);  // set che do CTC

  TIMSK2 |= (1 << OCIE2A);  // enable timer 2
}
void loop() {
  digitalWrite(EN_PIN, LOW);
  SpeedStep(-5);
  //digitalWrite(EN_PIN, HIGH);
}
void SpeedStep(int16_t x, int16_t sovong) {
  if (x < 0) {
    dir_step = -1;
    digitalWrite(DIR_PIN, LOW);
  } else if (x > 0) {
    dir_step = 1;
    digitalWrite(DIR_PIN, HIGH);
  } else {
    dir_step = 0;
  }
  vong = sovong;
  counter_bot = abs(x);
  counter_top = abs(x) / 2;
}