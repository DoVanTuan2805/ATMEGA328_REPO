#include <ArduinoJson.h>
#include "FirebaseESP8266.h"
#include<ESP8266WiFi.h>

//chân ST_CP của 74HC595
#define latchPin D2
//chân SH_CP của 74HC595
#define clockPin D3
//Chân DS của 74HC595
#define dataPin D1 

char *ssid = "NGOC XUAN";
char *pass = "01021967";

FirebaseData firebaseData;
WiFiClient client;
String path = "/";
FirebaseJson json;
unsigned long t1 = 0;

//mảng có 10 số (từ 0-9) và 
const int Seg[10] = {
  0b11000000,//0 - các thanh từ a-f sáng
  0b11111001,//1 - chỉ có 2 thanh b,c sáng
  0b10100100,//2
  0b10110000,//3
  0b10011001,//4
  0b10010010,//5
  0b10000010,//6
  0b11111000,//7
  0b10000000,//8
  0b10010000,//9
};


void setup() {
  //Bạn BUỘC PHẢI pinMode các chân này là OUTPUT
  pinMode(latchPin, OUTPUT);
  pinMode(clockPin, OUTPUT);
  pinMode(dataPin, OUTPUT);

  WiFi.disconnect();
  WiFi.mode(WIFI_STA);
  WiFi.begin (ssid, pass);
  Serial.begin(115200);
  Serial.println("Connecting...");
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.println("...");
  }
  Firebase.begin("test1-fc9fb-default-rtdb.firebaseio.com","QP07qcznXFzfmh36bUj0tBIjFHOyeKBaA8JbzSLR");
  Firebase.reconnectWiFi (true);
  Serial.println(WiFi.localIP());
}

void loop() { 
  static int point = 0;
  Firebase.getInt(firebaseData,path + "/test/datane");
  int x = firebaseData.intData();
  Serial.println(x);

  digitalWrite(latchPin, LOW);
  //Xuất bảng ký tự ra cho Module LED
  shiftOut(dataPin, clockPin, MSBFIRST, Seg[x]);  
  digitalWrite(latchPin, HIGH);
  
//  digitalWrite(latchPin, LOW);
//  //Xuất bảng ký tự ra cho Module LED
//  shiftOut(dataPin, clockPin, MSBFIRST, Seg[point]);  
//  digitalWrite(latchPin, HIGH);
    
//  point = (point + 1) % 10; // Vòng tuần hoàn từ 0--9
//  delay(500);//Đợi 0.5 s cho mỗi lần tăng số
}
