
#define SDI 13
#define LAT 12
#define CLK 11
#define LED 10

int led_hien_thi = 0, number, value = 100;
unsigned char hex_7seg[] ={0xC0, 0xF9, 0xA4, 0xB0, 0x99, 0x92, 0x82, 0xF8, 0x80, 0x90}; 
unsigned char led_show[]  ={0x00, 0x01, 0x02, 0x04, 0x08, 0x10, 0x20}; 
bool tt_led = 0;
int count = 0;
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
//    noInterrupts();
//  /* Reset Timer/Counter1 */
//  TCCR1A = 0;
//  TCCR1B = 0;
//  TIMSK1 = 0;
//  
//  /* Setup Timer/Counter1 */
//  TCNT1 = value;
//  TCCR1B |= (1 << CS10) | (1 << CS12);    // prescale = 64  
//  TIMSK1 = (1 << TOIE1);                  // Overflow interrupt enable 
//  interrupts();
//  Timer1.initialize(10); // khởi tạo timer 1 đến 1 giây
//  Timer1.attachInterrupt(quet_led); // khai báo ngắt timer 1
  pinMode (SDI, OUTPUT);
  pinMode (LAT, OUTPUT);
  pinMode (CLK, OUTPUT);
  pinMode (LED, OUTPUT);
}
ISR(TIMER1_OVF_vect) {
  TCNT1 = value;
  led_hien_thi++;
  //digitalWrite(LED, !tt_led );       // đảo trang thái led
  //count++;
  if(led_hien_thi == 5){
    led_hien_thi = 0;
  }
  else {
    hien_thi(number , led_hien_thi);
  }
}
void xuat_16bit(unsigned char hc595_1 , unsigned char hc595_2){
  digitalWrite(LAT, LOW);
  shiftOut(SDI, CLK, MSBFIRST, hc595_2);
  shiftOut(SDI, CLK, MSBFIRST, hc595_1);
  digitalWrite(LAT, HIGH);    
}
void hien_thi(int num, int tt){
  int nghin, tram, chuc, dvi;
  nghin = num / 1000;
  tram  = (num %  1000) / 100;
  chuc  = (num % 100) / 10;
  dvi   = (num % 10);
  if ( tt == 0 ) { xuat_16bit( hex_7seg[0],        led_show[tt]); }
  if ( tt == 1 ) { xuat_16bit( hex_7seg[nghin],    led_show[tt]); }
  if ( tt == 2 ) { xuat_16bit( hex_7seg[tram],     led_show[tt]); }
  if ( tt == 3 ) { xuat_16bit( hex_7seg[chuc],     led_show[tt]); }
  if ( tt == 4 ) { xuat_16bit( hex_7seg[dvi],      led_show[tt]); }
}
void quet_led(){
  led_hien_thi++;
  //digitalWrite(LED, !tt_led );       // đảo trang thái led
  //count++;
  if(led_hien_thi == 5){
    led_hien_thi = 0;
  }
  else {
    hien_thi(number , led_hien_thi);
  }
}
void loop() {
  number = 1230;
  //xuat_16bit(0x90, 0x01);
  //hien_thi(12, 1);
  //Serial.println(count);
}
