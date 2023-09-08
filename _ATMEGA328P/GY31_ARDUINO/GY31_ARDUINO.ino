#define s0 8
#define s1 9
#define s2 10
#define s3 11
#define out 12

int data = 0;
unsigned int red, green, blue;
int redMin = 20; // Red minimum value
int redMax = 40; // Red maximum value
int greenMin = 40; // Green minimum value
int greenMax = 70; // Green maximum value
int blueMin = 22; // Blue minimum value
int blueMax = 70; // Blue maximum value
String data_tx = "", data_rx;
void setup()
{
  pinMode(s0, OUTPUT);
  pinMode(s1, OUTPUT);
  pinMode(s2, OUTPUT);
  pinMode(s3, OUTPUT);
  pinMode(out, INPUT);

  Serial.begin(9600);

  digitalWrite(s0,HIGH);
  digitalWrite(s1,LOW);

}
static long t_prev = 0;
void loop()
{
  while(Serial.available()){
    data_rx =Serial.readStringUntil('\n');
  }
  read_color();
  if (millis() - t_prev > 500) {
    data_tx = data_tx + String(red) + "R" + String(green) + "G" + String(blue);
    Serial.println(data_tx);      // gui du lieu tu arduino len c#
    data_tx = "";
    t_prev = millis();
  }
}
void read_color() {
  digitalWrite(s2, LOW);       //S2/S3 levels define which set of photodiodes we are using LOW/LOW is for RED LOW/HIGH is for Blue and HIGH/HIGH is for green
  digitalWrite(s3, LOW);
  //  Serial.print("Red value= ");
  data = pulseIn(out, LOW); //here we wait until "out" go LOW, we start measuring the duration      and stops when "out" is HIGH again
  red = map(data,  redMin,redMax,255,0);
  if (red >= 255) {
    red = 255;
  }
  //  Serial.print(red);
  //  Serial.print("\t");
  delay(100);

  digitalWrite(s2, HIGH);
  digitalWrite(s3, HIGH);
  //  Serial.print("Green value= ");
  data = pulseIn(out, LOW); //here we wait until "out" go LOW, we start measuring the duration and stops when "out" is HIGH again
  green = map(data, greenMin,greenMax,255,0);
  if (green >= 255) {
    green = 255;
  }
  //  Serial.print(green);
  //  Serial.print("\t");
  delay(100);

  digitalWrite(s2, LOW);
  digitalWrite(s3, HIGH);
  //Serial.print("Blue value= ");
  data = pulseIn(out, LOW); //here we wait until "out" go LOW, we start measuring the duration and stops when "out" is HIGH again
  blue = map(data,  blueMin,blueMax,255,0);
  if (blue >= 255) {
    blue = 255;
  }
  //  Serial.print(blue);
  //  Serial.print("\t");
  delay(100);
  //Serial.println();
}
