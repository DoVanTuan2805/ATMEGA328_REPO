#include <MD_Parola.h>
#include <MD_MAX72xx.h>
#include <SPI.h>
#define HARDWARE_TYPE MD_MAX72XX::FC16_HW
// Defining size, and output pins
#define MAX_DEVICES 4
//#define CS_PIN 5
#define CLK_PIN   2
#define DATA_PIN  4
#define CS_PIN    3
char buf[10];
int i = 0;
int h = 10, m = 45;
String k;
textEffect_t texteffect[] = {
  PA_WIPE,
  PA_WIPE_CURSOR,
  PA_OPENING_CURSOR,
  PA_CLOSING_CURSOR,
  PA_BLINDS,
  PA_MESH,
  PA_OPENING,
  PA_CLOSING,
  PA_SCAN_VERT,
  PA_DISSOLVE,
  PA_RANDOM,
  PA_PRINT,
  PA_SCROLL_RIGHT,
  PA_SCROLL_LEFT,
  PA_GROW_UP,
  PA_GROW_DOWN,
  PA_SCROLL_UP,
  PA_SCROLL_DOWN,
  PA_SCROLL_UP_RIGHT,
  PA_SCROLL_UP_LEFT,
  PA_SCROLL_DOWN_RIGHT,
  PA_SCROLL_DOWN_LEFT,
};
MD_Parola myDisplay = MD_Parola(HARDWARE_TYPE, DATA_PIN, CLK_PIN, CS_PIN, MAX_DEVICES);
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  myDisplay.begin();
  myDisplay.setIntensity(0);
  myDisplay.setTextAlignment(PA_CENTER);
  myDisplay.setSpeed(80);
  myDisplay.setPause(2 000);
  myDisplay.displayClear();
}

void loop() {
  // put your main code here, to run repeatedly:

  //  if (Display.displayAnimate()) {
  //    Display.displayReset();
  //  }
  //m++;
  k = String(h) + ":" + String(m);
  Serial.println(k);
  for ( i = 0; i < sizeof(k); i++) {
    buf[i] = k[i];
    Serial.println(buf[i]);
  }
  if (myDisplay.displayAnimate()) {
    myDisplay.displayText(buf, myDisplay.getTextAlignment(), myDisplay.getSpeed(), myDisplay.getPause(), PA_GROW_UP, PA_GROW_DOWN);
    myDisplay.displayReset();
  }
}
