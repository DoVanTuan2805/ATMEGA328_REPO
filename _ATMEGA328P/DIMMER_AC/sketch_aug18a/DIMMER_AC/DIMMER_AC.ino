#define bt 5
int LAMP = 6;
int dim_val = 0;
int zero = 2;
int dimming_time = 128, dim_step = 500, dim =0;
void setup() {
  pinMode(LAMP, OUTPUT);
  pinMode(bt, INPUT);
  pinMode(A0, INPUT);
  Serial.begin(9600);
  attachInterrupt(digitalPinToInterrupt(zero), zero_cross, RISING);
}

void loop() {
}
void zero_cross() {
  dim_val= analogRead(A0); 
  Serial.println(dim_val);
//  dimming_time = (10 * dim_val);
  dimming_time = map (dim_val, 0, 1023 , 0 ,7000);
  delayMicroseconds(dimming_time);
  digitalWrite(LAMP, HIGH);
  delayMicroseconds(10);
  digitalWrite(LAMP, LOW);
}
