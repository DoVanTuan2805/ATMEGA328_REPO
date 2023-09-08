#define tb 9
int
  tt = 10,
  hh = 20,
  bui = 30,
  dienap = 40;
String str = "";
void setup() {
  Serial.begin(9600);

  String mess = 'a' + String(tb) + 'b' + String(tt) + 'c' + String(hh) +'d' + String(bui) + 'e' + String(dienap) + 'f';
  Serial.println(mess);
  int s = mess.indexOf("b") - mess.indexOf("a");
  int s1 = mess.indexOf("b");
  int s2 = mess.indexOf("a");
  long t1 = mess[mess.indexOf("a") + 1] - 48 ; // char(0-9) = (48-57) -> int(0-9) = char(0-9) - 48 
  Serial.print(s);
  Serial.print(" ---- ");
  Serial.print(s1);
  Serial.print(" ---- ");
  Serial.print(s2);
  Serial.print(" ---- ");
  Serial.print(t1);
  Serial.println();
  delay(1000);
}

void loop() {
}
