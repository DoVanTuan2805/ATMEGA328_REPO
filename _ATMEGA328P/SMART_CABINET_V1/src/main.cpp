#include <Arduino.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <Keypad.h>
#include <keypad_user.h>
LiquidCrystal_I2C lcd(0x27, 20, 4);

const int cash = 2; // connect blue wire to pin 15, purple to ground
uint8_t pulse;
uint8_t money = 0;
uint8_t counter = 0;

#define NUM_OF_SCREEN 4

typedef enum
{
  SCREEN1 = 0,
  SCREEN2 = 1,
  SCREEN3 = 2,
  SCREEN4 = 3,
} Screen_t;

bool ArrayScreen(Screen_t screen, bool *slot);
bool mainLcd(bool *slot);
bool cabinShow(bool *slot);
bool cabinhHour(bool *slot);
bool cabinhBill(bool *slot);

static bool (*handleScreen[NUM_OF_SCREEN])(bool *slot){
    [SCREEN1] = mainLcd,
    [SCREEN2] = cabinShow,
    [SCREEN3] = cabinhHour,
    [SCREEN4] = cabinhBill,
};

/* ------------- FUNCTION ------------------- */
void processInScreen(Screen_t screen, char dataKey, bool *slotCabin);
void getMoney();
/* ------------- FUNCTION ------------------- */

Screen_t page = SCREEN1;
bool arraySlot[6] = {true, false, false, false, false, false};
char keyPress;
typedef enum
{
  HOUR_6 = 0,
  HOUR_12 = 1
} CabinHour_t;
typedef enum
{
  SIZE_S = 0,
  SIZE_L = 1
} CabinSize_t;
typedef enum
{
  BILL_S = 10000,
  BILL_L = 20000
} CabinBill_t;

CabinHour_t cabinHour;
CabinSize_t cabinSize;

void setup()
{
  Serial.begin(9600);
  pinMode(cash, INPUT_PULLUP);
  Serial.println("Cash machine booted");
  lcd.init();
  lcd.backlight();
  lcd.clear();
}
void loop()
{
  keyPress = getKey();
  if (keyPress)
  {
    processInScreen(page, keyPress, arraySlot);
  }
  ArrayScreen(page, arraySlot);
}
void processInScreen(Screen_t screen, char dataKey, bool *slotCabin)
{
  if (screen == SCREEN1)
  {
    if (dataKey == '1') // LAY DO
    {
      page = SCREEN2;
      lcd.clear();
    }
    else if (dataKey == '2') // GUI DO
    {
      page = SCREEN2;
      lcd.clear();
    }
  }
  else if (screen == SCREEN2)
  {
    if (dataKey != '*' || dataKey != '#') // CHON TU
    {
      uint8_t numSlot = (dataKey - '0') - 1;
      Serial.println(numSlot);
      if (slotCabin[numSlot] == true)
      {
        page = SCREEN3;
        if (numSlot < 3)
        {
          cabinSize = SIZE_S;
        }
        else
        {
          cabinSize = SIZE_L;
        }
        lcd.clear();
      }
    }
  }
  else if (screen == SCREEN3)
  {
    if (dataKey == '1') // 6H
    {
      page = SCREEN4;
      cabinHour = HOUR_6;
      lcd.clear();
    }
    else if (dataKey == '2') // 12H
    {
      page = SCREEN4;
      cabinHour = HOUR_12;
      lcd.clear();
    }
  }
}
void getMoney()
{
  if (digitalRead(cash) == 0)
  {
    pulse = pulseIn(cash, LOW);
    Serial.println(pulse);
    if (pulse > 70)
    {
      Serial.println("Bill Accepted!");
      money = money + 1;
      Serial.print("money :");
      Serial.println(money);
      pulse = 0;
    }
    // Serial.println(pulse);
  }
  else if (digitalRead(cash) == 1)
  {
  }
}

bool ArrayScreen(Screen_t screen, bool *slot)
{
  if (screen < NUM_OF_SCREEN && (*handleScreen[screen] != NULL))
  {
    return handleScreen[screen](slot);
  }
  else
  {
    return false;
  }
}
bool mainLcd(bool *slot)
{
  lcd.setCursor(4, 0);
  lcd.print("1 : LAY DO !");
  lcd.setCursor(4, 2);
  lcd.print("2 : GUI DO !");
}
bool cabinShow(bool *slot)
{
  String dataTrong = "TRONG";
  String dataDay = "DAY !";
  String data;
  lcd.setCursor(0, 0);
  lcd.print("1(S)   2(S)   3(S)");
  lcd.setCursor(0, 2);
  lcd.print("4(L)   5(L)   6(L)");

  data = slot[0] == true ? dataTrong : dataDay;
  lcd.setCursor(0, 1);
  lcd.print(data);
  data = slot[1] == true ? dataTrong : dataDay;
  lcd.setCursor(7, 1);
  lcd.print(data);
  data = slot[2] == true ? dataTrong : dataDay;
  lcd.setCursor(14, 1);
  lcd.print(data);

  data = slot[3] == true ? dataTrong : dataDay;
  lcd.setCursor(0, 3);
  lcd.print(data);
  data = slot[4] == true ? dataTrong : dataDay;
  lcd.setCursor(7, 3);
  lcd.print(data);
  data = slot[5] == true ? dataTrong : dataDay;
  lcd.setCursor(14, 3);
  lcd.print(data);
}
bool cabinhHour(bool *slot)
{
  lcd.setCursor(0, 0);
  lcd.print("VUI LONG CHON :");
  lcd.setCursor(2, 2);
  lcd.print("1 - GUI : 6H");
  lcd.setCursor(2, 3);
  lcd.print("2 - GUI : 12H");
}
bool cabinhBill(bool *slot)
{
  lcd.setCursor(0, 0);
  if (cabinHour == HOUR_6)
  {
    if (cabinSize == SIZE_S)
    {
    }
  }
  lcd.print("TONG TIEN :  ");
  lcd.setCursor(2, 2);
  lcd.print("1 - GUI : 6H");
  lcd.setCursor(2, 3);
  lcd.print("2 - GUI : 12H");
  // lcd.setCursor(4, 0);
  // lcd.print("VUI LONG NHAP");
  // lcd.setCursor(5, 1);
  // lcd.print("MAT KHAU !!");
  // lcd.setCursor(0, 3);
  // lcd.print("4 SO :");
}