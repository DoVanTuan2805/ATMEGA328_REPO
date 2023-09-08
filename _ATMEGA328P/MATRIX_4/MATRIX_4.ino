#include <NTPClient.h>
#include <ESP8266WiFi.h>
#include <FirebaseESP8266.h>
#include <WiFiUdp.h>
#include <MD_Parola.h>
#include <MD_MAX72xx.h>
#include <SPI.h>

const char *ssid = "FPT Telecom-0876";
const char *pass = "tuan2805";
//*******************DEFINE FIREBASE***************************//
#define FIREBASE_HOST "https://esptest-25959-default-rtdb.firebaseio.com/"      //FIRE BASE ID ESPTEST
#define FIREBASE_AUTH "hd0Sv7oiw3cifDTLO4TYqGcFrJnc30edVJAMQYto"
FirebaseData fbdo;
FirebaseJson fbjon;
String path = "/";
int modes, speeds;
String c;
char buf[10];
//*******************END FIREBASE***************************//
int currentHour, currentMinute, currentSecond, i;
// Uncomment according to your hardware type
#define HARDWARE_TYPE MD_MAX72XX::FC16_HW
// Defining size, and output pins
#define MAX_DEVICES 4
//#define CS_PIN 5
#define DATA_PIN  14
#define CS_PIN    12
#define CLK_PIN   13

//*******************DEFINE MATRIX***************************//
MD_Parola Display = MD_Parola(HARDWARE_TYPE, DATA_PIN, CLK_PIN, CS_PIN, MAX_DEVICES);
//***************DEFINE SEVER GET TIME *********************//
WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP, "pool.ntp.org");
void setup() {
  Serial.begin(115200);
  Serial.println();
  Serial.println("Connecting AP ...");
  WiFi.begin(ssid, pass);
  while ( WiFi.status() != WL_CONNECTED ) {
    Serial.println("Connected failed .. !!");
    delay(1000);
  }
  Serial.print("AP Address : ");
  Serial.println(WiFi.localIP());
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
  Firebase.reconnectWiFi(true);
  if (! Firebase.beginStream(fbdo, path)) {
    Serial.println("REASON" + fbdo.errorReason());
    Serial.println();
  }
  //init time client
  timeClient.begin();
  timeClient.setTimeOffset(25200);
  //GMT +7 = 25200
  Display.begin();
  Display.setIntensity(0);
  Display.setTextAlignment(PA_CENTER);
  Display.setSpeed(100);
  Display.setPause(700);
  Display.displayClear();
}

void loop() {
  timeClient.update();
  //****************GET HOUR************//
  currentHour = timeClient.getHours();
  int chuc_gio = currentMinute / 10;
  int dvi_gio = currentMinute % 10;
  //****************GET MINUTES************//
  currentMinute = timeClient.getMinutes();
  int chuc_phut = currentMinute / 10;
  int dvi_phut = currentMinute % 10;
  //*******************************************************************************//
  c =  ":"+ String(currentHour) + ":" + String(chuc_phut) + String(dvi_phut)+ ":";
  for (i = 0; i < sizeof(c); i++) {
    buf[i] = c[i];
  }
  Firebase.getInt(fbdo, "/mode");
  modes = fbdo.intData();
  Firebase.getInt(fbdo, "/speed");
  speeds = fbdo.intData();
  Serial.println(modes);
  switch (modes) {
    case 1:
      Display.setTextAlignment(PA_CENTER);
      
      //Display.displayText(buf, Display.getTextAlignment(), Display.getSpeed(), Display.getPause(), PA_SCROLL_UP, PA_SCROLL_UP);
      Display.print(c);
      break;
    case 2:
      if (Display.displayAnimate()) {
        Display.displayText("HEY DO", Display.getTextAlignment(), Display.getSpeed(), Display.getPause(), PA_SCROLL_DOWN_LEFT, PA_SCROLL_DOWN_LEFT);
        Display.displayReset();
      }
      break;
  }
}
