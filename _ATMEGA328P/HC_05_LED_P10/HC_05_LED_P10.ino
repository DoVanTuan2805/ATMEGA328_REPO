#include <SPI.h>        //SPI.h must be included as DMD is written by SPI (the IDE complains otherwise)
#include <DMD.h>        //
#include <TimerOne.h>   //
#include "SystemFont5x7.h"
#include "Arial_Black_16_ISO_8859_1.h"
#include "fontVietNam.h"
#include <SoftwareSerial.h>
const byte rxPin = 2;         // TX SIM
const byte txPin = 3;         // RX SIM
SoftwareSerial Serial1 (rxPin, txPin); // hc 05
String str = "";
//Fire up the DMD library as dmd
#define DISPLAYS_ACROSS 1
#define DISPLAYS_DOWN 1
DMD dmd(DISPLAYS_ACROSS, DISPLAYS_DOWN);
#include "FontMaker.h"
#define BLUE    0x001F
#define RED     0xF800
#define GREEN   0x07E0
#define CYAN    0x07FF
#define MAGENTA 0xF81F
#define YELLOW  0xFFE0
#define BLACK  0x0000

char c = "";
String str1 = "";
/*--------------------------------------------------------------------------------------
  Interrupt handler for Timer1 (TimerOne) driven DMD refresh scanning, this gets
  called at the period set in Timer1.initialize();
  --------------------------------------------------------------------------------------*/
void ScanDMD()
{
  dmd.scanDisplayBySPI();
}

/*--------------------------------------------------------------------------------------
  setup
  Called by the Arduino architecture before the main loop begins
  --------------------------------------------------------------------------------------*/
void setup(void)
{
  Serial.begin(9600);
  Serial1.begin(9600);
  //initialize TimerOne's interrupt/CPU usage used to scan and refresh the display
  Timer1.initialize( 3000 );           //period in microseconds to call ScanDMD. Anything longer than 5000 (5ms) and you can see flicker.
  Timer1.attachInterrupt( ScanDMD );   //attach the Timer1 interrupt to ScanDMD which goes to dmd.scanDisplayBySPI()

  //clear/init the DMD pixels held in RAM
  dmd.clearScreen( true );   //true is normal (all pixels off), false is negative (all pixels on)
  Serial.begin(9600);
}
void setpx(int16_t x, int16_t y, uint16_t color) // hàm vẽ chữ
{
  dmd.writePixel(x, y, GRAPHICS_NORMAL, 1 ); //Thay đổi hàm này thành hàm vẽ pixel mà thư viện led bạn dùng cung cấp
}
MakeFont myfont(&setpx);
int i = 32;
void loop(void)
{
  //  while (Serial.available() > 0) {
  //    str = Serial.readString();
  //    str.trim();
  //    Serial.println(str);
  //    Serial1.print(str + "\r\n");
  //  }


  i--;
  myfont.set_font(MakeFont_Font1);
  myfont.print_noBackColor(i, 3, str1,  BLACK);
  delay(70);
  dmd.clearScreen( true );
  if (i == -100) {
    i = 32;
  }
  while (Serial1.available() > 0) { // nhận tín hiệu hc05
    c = Serial1.read();   // đọc tín hiệu hc 05
    //Serial.println(c);
    if (c != '\n' && c != '\r') { //loại bỏ kí tự
      str1 += c;
      if (c == '.') {
        str1 = "";
      }
    }
    if (c == '\n') {
      Serial.println(str1);
      //str1 = "";
    }

  }
}
