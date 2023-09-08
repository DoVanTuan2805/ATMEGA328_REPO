 
int randomm;
void setup()
{
  int i;
  for (i = 5; i <= 12;i++)
  {
    pinMode (i, OUTPUT);
  }
}
void trai_phai()
{
  int i;
  for (int i = 5;i <=12;i++)
  {
    digitalWrite (i , LOW);
    delay(50);
    digitalWrite (i , HIGH);
    delay(50);
  }
}

void phai_trai ()
{
  int i ;
  for (i = 12;i >= 5; i--)
  {
    digitalWrite (i , LOW);
    delay(50);
    digitalWrite (i , HIGH);
    delay(50);
    }
  }
void giua_2ben  ()
{
  digitalWrite(5,LOW);
  digitalWrite(12,LOW);
  delay(100);
  digitalWrite(5,HIGH);
  digitalWrite(12,HIGH);
  delay(100);
  digitalWrite(6,LOW);
  digitalWrite(11,LOW);
  delay(100);
  digitalWrite(6,HIGH);
  digitalWrite(11,HIGH);
  delay(100);
  digitalWrite(7,LOW);
  digitalWrite(10,LOW);
  delay(100);
  digitalWrite(7,HIGH);
  digitalWrite(10,HIGH);
  delay(100);
  digitalWrite(8,LOW);
  digitalWrite(9,LOW);
  delay(100);
  digitalWrite(8,HIGH);
  digitalWrite(9,HIGH);
  delay(100);
}
void triple_led()
{
  int i;
  for (i = 5;i <= 12;i++)
  {
    digitalWrite (i, LOW);
    digitalWrite (i+1, LOW);
    digitalWrite (i+2, LOW);
    delay(50);
    digitalWrite (i, HIGH);
    digitalWrite (i+1, HIGH);
    digitalWrite (i+2, HIGH);
    delay(50);
    }
  }
void led_rand()
{
  int a,i;
  for(i = 0; i < 8;i++)
  {
    a = random (5,13);
    digitalWrite (a, LOW);
    delay (50);
    digitalWrite (a, HIGH);
    delay(50);
  }
}
void loop() { 
  giua_2ben();
  triple_led();
  led_rand();
  trai_phai ();
  phai_trai();
}
