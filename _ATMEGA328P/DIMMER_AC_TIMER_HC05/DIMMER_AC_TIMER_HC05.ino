#include <SoftwareSerial.h>
#include <TimerOne.h>
volatile int i = 0;
volatile boolean zero_cross = 0;
int AC_pin = 6;
int dim = 128;
int inc = 1;

int freqStep = 75;

#define TX_HC 7
#define RX_HC 8
SoftwareSerial mySerial(RX_HC, TX_HC);  // RX, TX
int state = 0;
void setup() {  // Begin setup
  Serial.begin(9600);
  mySerial.begin(9600);
  pinMode(AC_pin, OUTPUT);
  pinMode(9,OUTPUT);
  attachInterrupt(0, zero_cross_detect, RISING);// ngắt ngoài nhận điểm zero
  Timer1.initialize(freqStep);	
  Timer1.attachInterrupt(dim_check, freqStep);// chu kì T = 150us
}

void zero_cross_detect() {
  zero_cross = true;
  i = 0;
  digitalWrite(AC_pin, LOW);
}

void dim_check() {
  digitalWrite(9, !digitalRead(9));
  if (zero_cross == true) {
	  // min 0% -> dim = 128 ---- i >= 128 -> 0.01  * 128 = 1.28s 	sáng
	  // max 100% -> dim = 0---- i >= 0 -> 0.01  * 0 = 0.01s 		sáng 
    if (i >= dim) {		
      digitalWrite(AC_pin, HIGH);
      i = 0;
      zero_cross = false;
    } else {	
      i++;
    }
  }
}

void loop() {
  if (mySerial.available() > 0) {
    state = mySerial.read();
  }

  if (state == '0') {
    mySerial.println("0%");
    dim = 128;			// 0% = 128
  } else if (state == '1') {
    mySerial.println("10%");
    dim = 112;
  } else if (state == '2') {
    mySerial.println("20%");
    dim = 98;
  } else if (state == '3') {
    mySerial.println("30%");
    dim = 84;
  } else if (state == '4') {
    mySerial.println("40%");
    dim = 70;
  } else if (state == '5') {
    mySerial.println("50%");
    dim = 56;
  } else if (state == '6') {
    mySerial.println("60%");
    dim = 42;
  } else if (state == '7') {
    mySerial.println("70%");
    dim = 28;
  } else if (state == '8') {
    mySerial.println("80%");
    dim = 14;
  } else if (state == '9') {
    mySerial.println("100%");
    dim = 0;
  }
  delay(60);
}