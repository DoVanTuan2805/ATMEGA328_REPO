#include <Servo.h>
#define bientroX  A0 
#define bientroY  A1 
#define servo 3
Servo myservo;
int button = 2;   

void setup ()
{
  myservo.attach(servo);
  pinMode(button, INPUT);
  pinMode(A0, INPUT);
  pinMode(A1, INPUT);
  Serial.begin(9600);
  
}

void loop ()
{
  int x = analogRead(bientroX);  // doc gia tri cua truc X
  int y = analogRead(bientroY);  // doc gia tri cua truc Y
  int KEY = digitalRead(button);  // doc gia tri cua nut nhan
  // Xuat ra cong Serial
  int giaTriGoc = map(y,0,1023,0,180);
  myservo.write(giaTriGoc);
  Serial.println(giaTriGoc);
  Serial.print("X="); Serial.println(x);
  Serial.print("Y="); Serial.println(y);
  Serial.print("KEY="); Serial.println(KEY); 
  Serial.println();
  delay(200);//delay để ổn định hơn
}
