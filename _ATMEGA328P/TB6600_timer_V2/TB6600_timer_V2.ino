#include <Arduino.h>
#include <avr/interrupt.h>

#define PIN_DIR 12
#define PIN_PUL 13

volatile uint16_t init_value_timer1 = 65500;
volatile uint16_t target_pulse = 1600;
volatile uint16_t current_pulse = 0;
volatile bool state = false;
volatile bool step_on = true;

String message = "";

ISR(TIMER1_OVF_vect) {
  state = !state;
  digitalWrite(PIN_PUL, state);
  TCNT1 = init_value_timer1;
  current_pulse++;
  if (current_pulse / 2 > target_pulse) {       // 3200 xung -> 1600 xung +    -------   1600 xung -
    current_pulse = 0;
    TCCR1A = 0;
    TCCR1B = 0;
    TIMSK1 = 0;
  }
}

void initInteruptTimer1() {
  cli();  // tắt ngắt toàn cục

  /* Reset Timer/Counter1 */
  TCCR1A = 0;
  TCCR1B = 0;
  TIMSK1 = 0;

  /* Setup Timer/Counter1 */
  TCCR1B |= (1 << CS11) | (1 << CS10);  // prescale = 64

  /*
  1 xung = 64/16Mhz = 4us
  */
  TCNT1 = init_value_timer1;      // DEFAUL = 65500 go to 65536 = 37 -> 4us * 37 = 148 tràn 
  TIMSK1 = (1 << TOIE1);  // Overflow interrupt enable
  sei();                  // cho phép ngắt toàn cục
}

void revDataFromUart() {
  if (Serial.available()) {
    char c = (char)Serial.read();
    if (c != '\n') {
      message += c;
    } else {
      Serial.println(message);
      if (message.length() > 0) {
        if (message.substring(0, 1) == "P") {         // PULSE / 1 ROUND
          target_pulse = message.substring(1).toInt() * 1600;
        }
        if (message.substring(0, 1) == "S") {       // RUN STEP
          initInteruptTimer1();
        }
        if (message.substring(0, 1) == "X") {       // STOP
          TCCR1A = 0;
          TCCR1B = 0;
          TIMSK1 = 0;
        }
        if (message.substring(0, 1) == "F") {       // SPEED
          init_value_timer1 = message.substring(1).toInt();
        }
        if (message.substring(0, 1) == "O") {       // 
          step_on = !step_on;
        }
        if (message.substring(0, 1) == "D") {     // DIR
          digitalWrite(PIN_DIR, message.substring(1).toInt());
        }
        message = "";
      }
    }
  }
}

void setup() {
  Serial.begin(9600);
  pinMode(PIN_DIR, OUTPUT);
  pinMode(PIN_PUL, OUTPUT);
  initInteruptTimer1();
}

void loop() {
  revDataFromUart();
}