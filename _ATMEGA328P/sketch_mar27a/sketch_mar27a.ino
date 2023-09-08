#include <Adafruit_MLX90614.h>
#include <SoftwareSerial.h>
Adafruit_MLX90614 mlx = Adafruit_MLX90614();
#define LED1 3
#define LED2 4
SoftwareSerial mySerial(11, 12);  // RX, TX
float temp_ambient = 33.29 , temp_obj = 35.29;
float temp_max, temp_min, temp_max_obj, temp_min_obj, temp_max_ambient, temp_min_ambient;
unsigned long count = 0, prev_time = 0, curr_time = 0, temp_check = 10;
String data, node, temp;
void setup()
{
  Serial.begin(9600);
  mySerial.begin(9600);
//  if (!mlx.begin())
//  {
//    while (1);
//  }
  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);
  temp = String(temp_obj) + "/" + String(temp_ambient);
  Serial.println(temp);
}
void loop() {
  curr_time = millis();
  if (Serial.available() > 0)
  {
    data = Serial.readStringUntil('\n');
    node = tach_chuoi(data, "/", 0);
    temp_min = (tach_chuoi(data, "/", 1)).toFloat();
    temp_max = (tach_chuoi(data, "/", 2)).toFloat();
    data = "";
  }
  if (node == "obj")
  {
    temp_max_obj = temp_max;
    temp_min_obj = temp_min;
  }
  if (node == "ambient")
  {
    temp_max_ambient = temp_max;
    temp_min_ambient = temp_min;
  }
  if (curr_time - prev_time > 1000)
  {
    prev_time = curr_time;
//    temp_obj = mlx.readObjectTempC();
//    temp_ambient = mlx.readAmbientTempC();
    temp = String(temp_obj) + "/" + String(temp_ambient);
    Serial.println(temp);
//    mySerial.println(temp_min_obj);
//    mySerial.println(temp_max_obj);
//    mySerial.println(temp_min_ambient);
//    mySerial.println(temp_max_ambient);
//    mySerial.println("-----");
  }
  checkTemp_obj(temp_obj, temp_min_obj, temp_max_obj);
  checkTemp_ambient(temp_ambient, temp_min_ambient, temp_max_ambient );

}
String tach_chuoi(String text, String ki_tu, uint16_t vi_tri)
{
  String tmp = text;
  for (int i = 0 ; i < vi_tri; i++) {
    tmp = tmp.substring(tmp.indexOf(ki_tu) + 1);
    if (tmp.indexOf(ki_tu) == -1 && i != vi_tri - 1) {       // neu ko tim thay ki tu (delim)tra ve -1
      return "";
    }
  }
  return tmp.substring(0, tmp.indexOf(ki_tu));
}
void checkTemp_obj(float temp_curr, float temp_min , float temp_max)
{
  if (temp_curr < temp_min || temp_curr > temp_max )
  {
    digitalWrite(LED1, HIGH);
  }
  else if (temp_min <= temp_curr && temp_curr <= temp_max)
  {
    digitalWrite(LED1, LOW);
  }
}
void checkTemp_ambient(float temp_curr, float temp_min , float temp_max)
{
  if (temp_curr < temp_min || temp_curr > temp_max )
  {
    digitalWrite(LED2, HIGH);
  }
  else if (temp_min <= temp_curr && temp_curr <= temp_max)
  {
    digitalWrite(LED2, LOW);
  }
}
