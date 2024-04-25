#include <Arduino.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <Keypad.h>
#include <keypad_user.h>
#include <ds1307.h>
LiquidCrystal_I2C lcd(0x27, 20, 4);
extern DateTime_t DateTimeNow;

/*  -------------- DEFINE PIN  --------------*/
const int cash = 2; // blue wire to UNO, purple to ground
#define INHIBIT 3
#define SDA_HC595 6
#define LAT_HC595 5
#define SCK_HC595 4
/*  -------------- DEFINE PIN  --------------*/
#define TIMEOUT 500
#define NUM_CABIN 6
#define NUM_OF_SCREEN 9
#define NUM_PASSWORD 5
#define TIMER_COUNT 65500
#define TIME_OPEN_CLOSE 3000

typedef enum
{
  BILL_S = 10000,
  BILL_L = 20000
} CabinBill_t;
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
  GET_DEPOSITE,
  PUT_DEPOSITE
} CabinMode_t;

CabinMode_t u_cabinMode;

typedef struct
{
  bool slot;
  CabinMode_t e_cabinMode;
  CabinHour_t e_cabinHour;
  CabinSize_t e_cabinSize;
  char passWord[NUM_PASSWORD];
  uint16_t bill_6H;
  uint16_t bill_12H;
  DateTime_t DateTimeInfor;
} CabinInfor_t;
CabinInfor_t cabinInfor[6];

typedef enum
{
  MAIN_LCD = 0,
  CABIN_SHOW,
  CABIN_HOUR,
  CABIN_BILL,
  CABIN_PASS,
  ERROR,
  CABIN_OPEN,
  CABIN_CLOSE,
  CABIN_WAIT_Q
} Screen_t;

bool ArrayScreen(Screen_t screen, CabinInfor_t *slotCabin);
bool mainLcd(CabinInfor_t *slotCabin);
bool cabinShow(CabinInfor_t *slotCabin);
bool cabinhHour(CabinInfor_t *slotCabin);
bool cabinhBill(CabinInfor_t *slotCabin);
bool cabinhPass(CabinInfor_t *slotCabin);
bool cabinhError(CabinInfor_t *slotCabin);
bool cabinhOpen(CabinInfor_t *slotCabin);
bool cabinhClose(CabinInfor_t *slotCabin);
bool cabinWaitQuestion(CabinInfor_t *slotCabin);

static bool (*handleScreen[NUM_OF_SCREEN])(CabinInfor_t *slotCabin){
    [MAIN_LCD] = mainLcd,
    [CABIN_SHOW] = cabinShow,
    [CABIN_HOUR] = cabinhHour,
    [CABIN_BILL] = cabinhBill,
    [CABIN_PASS] = cabinhPass,
    [ERROR] = cabinhError,
    [CABIN_OPEN] = cabinhOpen,
    [CABIN_CLOSE] = cabinhClose,
    [CABIN_WAIT_Q] = cabinWaitQuestion,
};

/* ------------- FUNCTION ------------------- */
void processInScreen(Screen_t screen, char dataKey, CabinInfor_t *slotCabin);
bool getMoney();
void out8bitHC595(uint8_t data);
/* ------------- FUNCTION ------------------- */

Screen_t page = MAIN_LCD;
bool arraySlot[6] = {true, false, false, false, false, false};
char keyPress;

uint8_t customerChoose;
uint8_t pulse;
uint32_t money = 0;
uint32_t totalBill;
uint64_t timeBillToPass, timErrToMain, timWaitToOpen, timeOpenToClose, timePassToQues;
static uint8_t indexPass = 0;

volatile uint8_t dataHC05 = 0b00111011;
volatile uint8_t toggle1;
ISR(TIMER1_COMPA_vect)
{
  out8bitHC595(dataHC05);
}
void setup()
{
  Serial.begin(9600);
  pinMode(cash, INPUT_PULLUP);
  Serial.println("Cash machine booted");
  pinMode(SDA_HC595, OUTPUT);
  pinMode(LAT_HC595, OUTPUT);
  pinMode(SCK_HC595, OUTPUT);
  pinMode(INHIBIT, OUTPUT);
  /* INIT TIMER 1*/
  cli(); // stop interrupts
  // Initialize Timer1
  TCCR1A = 0; // set entire TCCR1A register to 0
  TCCR1B = 0; // same for TCCR1B
  TCNT1 = 0;  // initialize counter value to 0
  // set compare match register for 1hz increments
  OCR1A = 15624; // 312; // = (16*10^6) / (1*1024) - 1 (must be <65536)
  // turn on CTC mode
  TCCR1B |= (1 << WGM12);
  // Set CS12 and CS10 bits for 1024 prescaler
  TCCR1B |= (1 << CS12) | (1 << CS10);
  // enable timer compare interrupt
  TIMSK1 |= (1 << OCIE1A);
  sei(); // allow interrupts
  /* INIT TIMER 1*/
  Wire.begin();
  lcd.init();
  lcd.backlight();
  lcd.clear();
  for (int i = 0; i < NUM_CABIN / 2 + 1; i++) // 4 NHO
  {
    cabinInfor[i].slot = true;
    cabinInfor[i].bill_6H = BILL_S;
    cabinInfor[i].bill_12H = BILL_S * 2;
  }
  for (int j = NUM_CABIN / 2 + 1; j < NUM_CABIN; j++) // 2 LON
  {
    cabinInfor[j].slot = true;
    cabinInfor[j].bill_6H = BILL_L;
    cabinInfor[j].bill_12H = BILL_L * 2;
  }
  // setTime(9, 42, 0, 2, 9, 1, 23); // 17:30:00 CN 5-1-2023
  dataHC05 = 0x00;
}
void loop()
{
  readDS1307();
  digitalWrite(INHIBIT, 1);

  keyPress = getKey();
  if (keyPress)
  {
    Serial.print("Key :");
    Serial.print(keyPress);
    Serial.println();
    processInScreen(page, keyPress, cabinInfor);
  }
  ArrayScreen(page, cabinInfor);
}
void processInScreen(Screen_t screen, char dataKey, CabinInfor_t *slotCabin)
{
  if (screen == MAIN_LCD)
  {
    if (dataKey == '1') // LAY DO
    {
      page = CABIN_SHOW;
      u_cabinMode = PUT_DEPOSITE;
      lcd.clear();
    }
    else if (dataKey == '2') // GUI DO
    {
      page = CABIN_SHOW;
      u_cabinMode = GET_DEPOSITE;
      lcd.clear();
    }
  }
  else if (screen == CABIN_SHOW)
  {
    if (dataKey == '#' || dataKey == '*')
    {
      page = MAIN_LCD;
      lcd.clear();
    }
    else if (dataKey != '*' || dataKey != '#') // CHON TU
    {

      uint8_t numSlot = (dataKey - '0') - 1;
      slotCabin[numSlot].e_cabinMode = u_cabinMode; // LAY CHE DO
      Serial.println(numSlot);
      if (slotCabin[numSlot].e_cabinMode == PUT_DEPOSITE) // CHE DO GUI DO
      {
        if (slotCabin[numSlot].slot == true) // TRONG
        {
          customerChoose = numSlot;
          page = CABIN_HOUR;
          lcd.clear();
        }
        else if (slotCabin[numSlot].slot == false) // DAY
        {
          page = ERROR;
          timErrToMain = millis();
          lcd.clear();
        }
      }
      else if (slotCabin[numSlot].e_cabinMode == GET_DEPOSITE) // CHE DO LAY DO
      {
        if (slotCabin[numSlot].slot == false) // DAY
        {
          customerChoose = numSlot;
          page = CABIN_PASS;
          lcd.clear();
        }
        else if (slotCabin[numSlot].slot == true) // TRONG
        {
          page = ERROR;
          timErrToMain = millis();
          lcd.clear();
        }
      }
    }
  }
  else if (screen == CABIN_HOUR)
  {
    if (dataKey == '1') // 6H
    {
      page = CABIN_BILL;
      cabinInfor[customerChoose].e_cabinHour = HOUR_6;
      totalBill = cabinInfor[customerChoose].bill_6H;
      money = 0;
      lcd.clear();
    }
    else if (dataKey == '2') // 12H
    {
      page = CABIN_BILL;
      cabinInfor[customerChoose].e_cabinHour = HOUR_12;
      totalBill = cabinInfor[customerChoose].bill_12H;
      money = 0;
      lcd.clear();
    }
    // if (cabinInfor[customerChoose].e_cabinHour == HOUR_6)
    // {
    //   totalBill = cabinInfor[customerChoose].bill_6H;
    // }
    // else if (cabinInfor[customerChoose].e_cabinHour == HOUR_12)
    // {
    //   totalBill = cabinInfor[customerChoose].bill_12H;
    // }
  }
  else if (screen == CABIN_PASS) // GET PASS
  {
    if (slotCabin[customerChoose].e_cabinMode == PUT_DEPOSITE) // CHE DO GUI DO
    {
      if (dataKey == '#')
      {
        /// RELAY ON
        page = CABIN_OPEN;
        slotCabin[customerChoose].slot = false;
        timWaitToOpen = millis();
        indexPass = 0;
        lcd.clear();
      }
      else if (dataKey != '*' || dataKey != '#')
      {
        if (indexPass < 4)
        {
          indexPass++;
          slotCabin[customerChoose].passWord[indexPass] = dataKey;
          lcd.setCursor(0, 3);
          lcd.print("                   ");
        }
        else
        {
          indexPass = 0;
          lcd.setCursor(0, 3);
          lcd.print("                   ");
        }
        Serial.print("Index Pass :");
        Serial.print(indexPass);
        Serial.println();
      }
    }
    else if (slotCabin[customerChoose].e_cabinMode == GET_DEPOSITE) // CHE DO LAY DO
    {
      static char passPress[NUM_PASSWORD];
      if (dataKey == '#')
      {
        /// RELAY ON
        bool result = memcmp(slotCabin[customerChoose].passWord, passPress, NUM_PASSWORD);
        if (result == 0)
        {
          page = CABIN_WAIT_Q;
          slotCabin[customerChoose].slot = true;
          indexPass = 0;
          lcd.clear();
        }
        else
        {
          page = ERROR;
          indexPass = 0;
          timErrToMain = millis();
          lcd.clear();
        }
      }
      else if (dataKey != '*' || dataKey != '#')
      {
        if (indexPass < 4)
        {
          indexPass++;
          passPress[indexPass] = dataKey;
          lcd.setCursor(0, 3);
          lcd.print("                   ");
        }
        else
        {
          indexPass = 0;
          lcd.setCursor(0, 3);
          lcd.print("                   ");
        }
        Serial.print("Index Pass :");
        Serial.print(indexPass);
        Serial.println();
      }
    }
  }
  else if (screen == CABIN_WAIT_Q)
  {
    if (dataKey == '1') // SU DUNG TIEP
    {
      page = CABIN_OPEN;
      timWaitToOpen = millis();
      slotCabin[customerChoose].slot = false;
      lcd.clear();
    }
    else if (dataKey == '2') // KO SU DUNG TIEP
    {
      page = CABIN_OPEN;
      slotCabin[customerChoose].slot = true;
      timWaitToOpen = millis();
      lcd.clear();
    }
  }
}
bool getMoney()
{
  pulse = pulseIn(cash, LOW);
  Serial.println(pulse);
  if (pulse > 50)
  {
    Serial.println("Bill Accepted!");
    money += 10000;
    // Serial.print("money :");
    // Serial.println(money);
    pulse = 0;
    return true;
  }
  return false;
}

bool ArrayScreen(Screen_t screen, CabinInfor_t *slotCabin)
{
  if (screen < NUM_OF_SCREEN && (*handleScreen[screen] != NULL))
  {
    return handleScreen[screen](slotCabin);
  }
  else
  {
    return false;
  }
}
bool mainLcd(CabinInfor_t *slotCabin)
{
  char dataLine[20];
  lcd.setCursor(4, 0);
  lcd.print("1 : GUI DO !");
  lcd.setCursor(4, 2);
  lcd.print("2 : LAY DO !");
  sprintf(dataLine, "%d-%d-%d  %d:%d:%d", DateTimeNow.day, DateTimeNow.month, DateTimeNow.year, DateTimeNow.hour, DateTimeNow.minute, DateTimeNow.second);
  lcd.setCursor(0, 3);
  lcd.print(dataLine);
}
bool cabinShow(CabinInfor_t *slotCabin)
{
  String dataTrong = "TRONG";
  String dataDay = "DAY !";
  String data;
  lcd.setCursor(0, 0);
  lcd.print("1(S)   2(S)   3(S)");
  lcd.setCursor(0, 2);
  lcd.print("4(S)   5(L)   6(L)");

  data = slotCabin[0].slot == true ? dataTrong : dataDay;
  lcd.setCursor(0, 1);
  lcd.print(data);
  data = slotCabin[1].slot == true ? dataTrong : dataDay;
  lcd.setCursor(7, 1);
  lcd.print(data);
  data = slotCabin[2].slot == true ? dataTrong : dataDay;
  lcd.setCursor(14, 1);
  lcd.print(data);

  data = slotCabin[3].slot == true ? dataTrong : dataDay;
  lcd.setCursor(0, 3);
  lcd.print(data);
  data = slotCabin[4].slot == true ? dataTrong : dataDay;
  lcd.setCursor(7, 3);
  lcd.print(data);
  data = slotCabin[5].slot == true ? dataTrong : dataDay;
  lcd.setCursor(14, 3);
  lcd.print(data);
}
bool cabinhHour(CabinInfor_t *slotCabin)
{
  lcd.setCursor(0, 0);
  lcd.print("VUI LONG CHON :");
  lcd.setCursor(2, 2);
  lcd.print("1 - GUI : 6H");
  lcd.setCursor(2, 3);
  lcd.print("2 - GUI : 12H");
}
bool cabinhBill(CabinInfor_t *slotCabin)
{
  char data[20];

  lcd.setCursor(0, 0);
  lcd.print("TONG TIEN :  ");
  lcd.print(totalBill);

  if (money < totalBill)
  {
    sprintf(data, "TIEN DA NHAN : %ld", money);
    lcd.setCursor(0, 1);
    lcd.print(data);
    digitalWrite(INHIBIT, 0);
    while (true)
    {
      if (getMoney() == true)
      {
        sprintf(data, "TIEN DA NHAN : %ld", money);
        lcd.setCursor(0, 1);
        lcd.print(data);
        Serial.println(data);
        memset(data, '\0', sizeof(data));
        if (money >= totalBill)
        {
          sprintf(data, "DA NHAN DU TIEN !");
          slotCabin[customerChoose].DateTimeInfor = DateTimeNow;
          lcd.setCursor(0, 2);
          lcd.print(data);
          timeBillToPass = millis();
          break;
        }
      }
    }
  }
  if (millis() - timeBillToPass > 3000)
  {
    page = CABIN_PASS;
    lcd.clear();
  }
}
bool cabinhPass(CabinInfor_t *slotCabin)
{
  char dataLine[20];
  String passHide;
  static uint8_t prevIndexPass;
  if (prevIndexPass != indexPass)
  {
    prevIndexPass = indexPass;
    if (indexPass == 0)
    {
      passHide = "";
    }
    for (int i = 0; i < indexPass; i++)
    {
      passHide += "*";
    }
  }
  lcd.setCursor(4, 0);
  lcd.print("VUI LONG NHAP");
  lcd.setCursor(5, 1);
  lcd.print("MAT KHAU !!");
  if (slotCabin[customerChoose].slot == false)
  {
    uint32_t totalTimeNow = DateTimeNow.hour * 60 * 60 +
                            DateTimeNow.minute * 60 +
                            DateTimeNow.second;
    uint32_t totalTimeSlot = slotCabin[customerChoose].DateTimeInfor.hour * 60 * 60 +
                             slotCabin[customerChoose].DateTimeInfor.minute * 60 +
                             slotCabin[customerChoose].DateTimeInfor.second;
    uint32_t timeRemain = totalTimeNow - totalTimeSlot;

    uint8_t h = timeRemain / (60 * 60);
    uint8_t m = timeRemain / 60 % 60;
    uint8_t s = timeRemain % 60;
    sprintf(dataLine, "%2d:%2d:%2d ", h, m, s);
    lcd.setCursor(0, 2);
    lcd.print("TG SU DUNG:");
    lcd.print(dataLine);
    memset(dataLine, " ", sizeof(dataLine));
  }
  lcd.setCursor(0, 3);
  lcd.print("4 SO :");
  lcd.print(passHide);
}
bool cabinhError(CabinInfor_t *slotCabin)
{
  lcd.setCursor(0, 0);
  lcd.print("VUI LONG THU LAI !");
  if (millis() - timErrToMain > 3000)
  {
    page = MAIN_LCD;
    lcd.clear();
  }
}
bool cabinhOpen(CabinInfor_t *slotCabin)
{
  lcd.setCursor(0, 0);
  lcd.print("TU DO DANG MO !");
  // 0b 0000 0000 ->     0x00
  // 0b 0000 0001
  dataHC05 |= (1 << customerChoose); // ON RELAY 1
  if (millis() - timWaitToOpen > TIME_OPEN_CLOSE)
  {
    page = CABIN_CLOSE;
    timeOpenToClose = millis();
    lcd.clear();
  }
}
bool cabinhClose(CabinInfor_t *slotCabin)
{
  lcd.setCursor(0, 0);
  lcd.print("TU DO DANG DONG !");
  // 0b 0000 0001 -> 0x01
  // 0b 0000 0000
  if (millis() - timeOpenToClose > TIME_OPEN_CLOSE)
  {
    dataHC05 &= ~(1 << customerChoose); // OFF RELAY 1
    page = MAIN_LCD;
    lcd.clear();
  }
}
bool cabinWaitQuestion(CabinInfor_t *slotCabin)
{
  lcd.setCursor(0, 0);
  lcd.print("BAN CO MUON TIEP TUC");
  lcd.setCursor(0, 1);
  lcd.print("SU DUNG TU KHONG ?");
  lcd.setCursor(0, 3);
  lcd.print(" 1-CO     2-KHONG ");
}
void out8bitHC595(uint8_t data)
{
  digitalWrite(LAT_HC595, LOW);
  shiftOut(SDA_HC595, SCK_HC595, MSBFIRST, data);
  digitalWrite(LAT_HC595, HIGH);
}
