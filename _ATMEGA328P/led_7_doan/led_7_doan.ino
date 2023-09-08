
void setup()
{
  pinMode(8, OUTPUT); //G
  pinMode(7, OUTPUT);//F
  pinMode(6, OUTPUT);//E
  pinMode(5, OUTPUT);//D
  pinMode(4, OUTPUT);//C
  pinMode(3, OUTPUT); //B
  pinMode(2,OUTPUT ); // A
}

void loop()
{
  for (int num = 0; num <= 9; num++)
    {
      number_led(num);
      delay(200);
    }
    
}
void number_led (int num)
{
  switch (num)
  {
    case 0:
      digitalWrite(2, LOW);
    digitalWrite(3, LOW);
      digitalWrite(4, LOW);
      digitalWrite(5, LOW);
      digitalWrite(6, LOW);
      digitalWrite(7, LOW);
      digitalWrite(8, HIGH);
      break;
    case 1:
      digitalWrite(2, HIGH);
    digitalWrite(3, LOW);
      digitalWrite(4, LOW);
      digitalWrite(5, HIGH);
      digitalWrite(6, HIGH);
      digitalWrite(7, HIGH);
      digitalWrite(8, HIGH);
      break;
    case 2:
      digitalWrite(2, LOW);
    digitalWrite(3, LOW);
      digitalWrite(4, HIGH);
      digitalWrite(5, LOW);
      digitalWrite(6, LOW);
      digitalWrite(7, HIGH);
      digitalWrite(8, LOW);
      break;
    case 3:
      digitalWrite(2, LOW);
    digitalWrite(3, LOW);
      digitalWrite(4, LOW);
      digitalWrite(5, LOW);
      digitalWrite(6, HIGH);
      digitalWrite(7, HIGH);
      digitalWrite(8, LOW);
      break;
    case 4 :
      digitalWrite(2, HIGH);
    digitalWrite(3, LOW);
      digitalWrite(4, LOW);
      digitalWrite(5, HIGH);
      digitalWrite(6, HIGH);
      digitalWrite(7, LOW);
      digitalWrite(8, LOW);
      break;
    case 5:
      digitalWrite(2, LOW);
    digitalWrite(3, HIGH);
      digitalWrite(4, LOW);
      digitalWrite(5, LOW);
      digitalWrite(6, HIGH);
      digitalWrite(7, LOW);
      digitalWrite(8, LOW);
      break;
    case 6:
      digitalWrite(2, LOW);
    digitalWrite(3, HIGH);
      digitalWrite(4, LOW);
      digitalWrite(5, LOW);
      digitalWrite(6, LOW);
      digitalWrite(7, LOW);
      digitalWrite(8, LOW);
      break;
    case 7:
      digitalWrite(2, LOW);
    digitalWrite(3, LOW);
      digitalWrite(4, LOW);
      digitalWrite(5, HIGH);
      digitalWrite(6, HIGH);
      digitalWrite(7, HIGH);
      digitalWrite(8, HIGH);
      break;
    case 8:
      digitalWrite(2, LOW);
    digitalWrite(3, LOW);
      digitalWrite(4, LOW);
      digitalWrite(5, LOW);
      digitalWrite(6, LOW);
      digitalWrite(7, LOW);
      digitalWrite(8, LOW);
      break;
    case 9:
      digitalWrite(2, LOW);
    digitalWrite(3, LOW);
      digitalWrite(4, LOW);
      digitalWrite(5, LOW);
      digitalWrite(6, HIGH);
      digitalWrite(7, LOW);
      digitalWrite(8, LOW);
      break;
  }
}
