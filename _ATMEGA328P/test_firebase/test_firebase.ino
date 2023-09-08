#include <ESP8266WiFi.h>
#include <Firebase8266.h>

#define HOST "test1-fc9fb-default-rtdb.firebaseio.com"
#define AUTH "QP07qcznXFzfmh36bUj0tBIjFHOyeKBaA8JbzSLR"

#define ssid "NGOC XUAN"
#define pass "01021967"

void setup() {
  Serial.begin(115200);
  WiFi.begin(ssid,pass);
  while (!WiFi.status() == WL_CONNECTED);
  {
    Serial.println(".");
  }
  Serial.println("connected");
  Serial.println(WiFi.localIP());
  Firebase.begin(HOST,AUTH);
  
}

void loop() {
  // put your main code here, to run repeatedly:

}
