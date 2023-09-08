#define SDI 4
#define LAT 3
#define CLK 2
int led_hien_thi, number, i;
int timer1_compare_match;
unsigned char hex_7seg[] = {0xC0, 0xF9, 0xA4, 0xB0, 0x99, 0x92, 0x82, 0xF8, 0x80, 0x90};
unsigned char led_show[]  = {0x00, 0x01, 0x02, 0x04, 0x08};
void xuat_1byte (unsigned int byte_xuat) {
  for ( int i = 0 ; i < 8 ; i++) {
    if ( (byte_xuat << i ) & 0x80) {
      digitalWrite(SDI, HIGH);
    }
    else {
      digitalWrite(SDI, LOW);
    }
    digitalWrite(CLK, LOW);
    digitalWrite(CLK, HIGH);
  }
}
void xuat_16bit(unsigned char hc595_1 , unsigned char hc595_2) {
  digitalWrite(LAT, LOW);
  xuat_1byte(hc595_2);
  xuat_1byte(hc595_1);
  digitalWrite(LAT, HIGH);
}
void hien_thi(int num, int tt) {
  int nghin, tram, chuc, dvi;
  nghin = num / 1000;
  tram  = (num %  1000) / 100;
  chuc  = (num % 100) / 10;
  dvi   = (num % 10);
  if ( tt == 0 ) {
    xuat_16bit( hex_7seg[0],        led_show[tt]);
  }
  if ( tt == 1 ) {
    xuat_16bit( hex_7seg[nghin],    led_show[tt]);
  }
  if ( tt == 2 ) {
    xuat_16bit( hex_7seg[tram],     led_show[tt]);
  }
  if ( tt == 3 ) {
    xuat_16bit( hex_7seg[chuc],     led_show[tt]);
  }
  if ( tt == 4 ) {
    xuat_16bit( hex_7seg[dvi],      led_show[tt]);
  }
}
void quet_led() {

}
ISR(TIMER1_OVF_vect) {
  TCNT1 = timer1_compare_match;
  led_hien_thi++;
  if (led_hien_thi == 5) {
    led_hien_thi = 0;
  }
  else {
    hien_thi(number , led_hien_thi);
  }
}
void setup() {
  Serial.begin(9600);
  pinMode (SDI, OUTPUT);
  pinMode (LAT, OUTPUT);
  pinMode (CLK, OUTPUT);
  noInterrupts();
  // Initialize Timer1
  timer1_compare_match = 65000;
  TCCR1A = 0;
  TCCR1B = 0;
  TIMSK1 = 0;

  /* Setup Timer/Counter1 */
  TCCR1B |= (1 << CS11) | (1 << CS10);    // prescale = 64
  TCNT1 = timer1_compare_match;
  TIMSK1 = (1 << TOIE1);
  interrupts();
}

void loop() {
  for ( i = 0 ; i < 1000; i++) {
    number = i;
    delay(100);
  }
  number = 0;
}
