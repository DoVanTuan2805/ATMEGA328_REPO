#include <LiquidCrystal_I2C.h>
#include <Wire.h>
LiquidCrystal_I2C lcd(0x27, 20, 4);
#define CB1 2         // NHAN BIET CHAI  -> ROT
#define CB2 18        // NHAN BIET CHAI  -> DONG NAP
#define Relay_Bom 10  //   ROT  TU DONG THEO CAM BIEN
// nut nhan
#define Button_Power 22
#define Button_Start 23
#define Button_Stop 24
#define Button_Conveyor1 25
#define Button_Conveyor2 26
#define Button_Rot 27
#define Button_Turntable 28
#define nut_tang_tt 29
#define nut_giam_tt 30
#define nut_tang_sl 31
#define nut_giam_sl 32
// relay
#define Relay_Power 42
#define Relay_Start 43
#define Relay_Stop 44
#define Relay_Conveyor1 45
#define Relay_Conveyor2 46

#define Relay_Rot 47        /// TUY CHINH ROT CHO SU CO
#define Relay_Turntable 48  ///  BAN XOAY

int GiaTriCamBien, GiaTriCamBien_2;
int sensorPin = A0;

int GiaTriTheTich, GiaTriTheTich_s, so_luong;
int nut_tang_State, nut_tang_State_s;
int nut_giam_State, nut_giam_State_s;
int nut_tang_so_luong, nut_tang_so_luong_s;
int nut_giam_so_luong, nut_giam_so_luong_s;
int So_Luong_Con_Lai, M, So_Luong_Con_Lai2;
unsigned long thoigianQK, Cambien;  // thời gian kể từ khi chương trình khởi động
bool tRot = 0;
unsigned long hientai = 0;
unsigned long thoigian;

bool statusCB1 = false;
bool statusWait = false;
unsigned long startROT;
unsigned long timeWait;
void CB_ROT_interrupt() {
  statusWait = true;
  statusCB1 = true;
  Turntable_Off();
  timeWait = millis();
}

void setup() {
  pinMode(CB1, INPUT);
  bool checkFullWater = false;
  uint64_t timeFuleWater;
  // nut nhan
  pinMode(Button_Power, INPUT);
  pinMode(Button_Start, INPUT);
  pinMode(Button_Stop, INPUT);
  pinMode(Button_Conveyor1, INPUT);
  pinMode(Button_Conveyor2, INPUT);
  pinMode(Button_Rot, INPUT);
  pinMode(Button_Turntable, INPUT);
  // relay
  pinMode(Relay_Power, OUTPUT);
  pinMode(Relay_Start, OUTPUT);
  pinMode(Relay_Stop, OUTPUT);
  pinMode(Relay_Conveyor1, OUTPUT);
  pinMode(Relay_Conveyor2, OUTPUT);
  pinMode(Relay_Rot, OUTPUT);
  pinMode(Relay_Turntable, OUTPUT);
  //  digitalWrite(Relay, LOW);     // NO -> ko bom
  pinMode(Relay_Bom, OUTPUT);
  //Version 1
  pinMode(nut_tang_tt, INPUT_PULLUP);
  pinMode(nut_giam_tt, INPUT_PULLUP);
  Serial.begin(9600);
  lcd.init();
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print(" The Tich:");
  lcd.setCursor(0, 1);
  lcd.print(" So Luong:");
  lcd.setCursor(0, 2);
  lcd.print("  Con Lai:");
  lcd.setCursor(0, 3);
  lcd.print("Thoi Gian:");
  // setup so luong
  pinMode(nut_tang_sl, INPUT_PULLUP);
  pinMode(nut_giam_sl, INPUT_PULLUP);
  digitalWrite(Relay_Bom, LOW);  // NO -> ko bom
  // NGAT ROT
  attachInterrupt(digitalPinToInterrupt(CB1), CB_ROT_interrupt, FALLING);
}
void loop() {


  if (Button_Power == LOW) {
    Power();
  }
  if (Button_Start == LOW) {
    Start();
  }
  if (Button_Stop == LOW) {
    Stop();
  }
  if (Button_Conveyor1 == HIGH) {
    Conveyor1_On();
  }
  if (Button_Conveyor1 == LOW) {
    Conveyor1_Off();
  }
  if (Button_Conveyor2 == HIGH) {
    Conveyor2_On();
  }
  if (Button_Conveyor2 == LOW) {
    Conveyor2_Off();
  }
  if (Button_Rot == HIGH) {
    Bat_Rot();
  }
  if (Button_Rot == LOW) {
    Tat_Rot();
  }
  if (Button_Turntable == HIGH) {
    Turntable_On();
  }
  if (Button_Turntable == LOW) {
    Turntable_Off();
  }
  nut_tang_State = digitalRead(nut_tang_tt);
  if (nut_tang_State_s == LOW && nut_tang_State == HIGH) {
    GiaTriTheTich = GiaTriTheTich + 100;
    delay(50);
  }

  nut_giam_State = digitalRead(nut_giam_tt);
  if (nut_giam_State_s == LOW && nut_giam_State == HIGH) {
    GiaTriTheTich = GiaTriTheTich - 100;
    delay(50);
  }
  nut_tang_so_luong = digitalRead(nut_tang_sl);
  if (nut_tang_so_luong_s == LOW && nut_tang_so_luong == HIGH) {
    so_luong = so_luong + 100;
    So_Luong_Con_Lai = So_Luong_Con_Lai + 100;
    delay(50);
  }

  nut_giam_so_luong = digitalRead(nut_giam_sl);
  if (nut_giam_so_luong_s == LOW && nut_giam_so_luong == HIGH) {
    so_luong = so_luong - 100;
    So_Luong_Con_Lai = So_Luong_Con_Lai - 100;
    delay(50);
  }
  if (GiaTriTheTich <= 0) {
    GiaTriTheTich = 0;
  }
  if (GiaTriTheTich >= 1000) {
    GiaTriTheTich = 1000;
  }
  if (so_luong <= 0) {
    so_luong = 0;
  }
  if (so_luong >= 1000) {
    so_luong = 1000;
  }

  if (So_Luong_Con_Lai <= 0) {
    So_Luong_Con_Lai = 0;
  }
  if (So_Luong_Con_Lai >= 1000) {
    So_Luong_Con_Lai = 1000;
  }
  Calc(GiaTriTheTich);
  float Bien_So_1 = 18;
  float NamTramMililit = (GiaTriTheTich * Bien_So_1);  // 44500
  float Mililit = NamTramMililit;
  float Bien_Tam = Mililit;                        // 22250
  float Bien_Tam_2 = Bien_Tam / 1000;              //22.25 giây
  float Giay_Tam = Bien_Tam_2 * So_Luong_Con_Lai;  // tổng số giây 11125
  float Phut_Tam = Giay_Tam / 60;                  //185.42
  float Gio_Tam = Phut_Tam / 60;                   //3.09
  int Gio_Tam2 = Gio_Tam;
  int Phut_Tam2 = Phut_Tam;
  int Giay = Giay_Tam - (Phut_Tam2 * 60);
  int Phut = float(Phut_Tam - Gio_Tam2 * 60);
  int Gio = float(Phut_Tam / 60);


  if (statusCB1 == true) {
    if (millis() - timeWait >= 2000) {
      startROT = millis();
      ROT_ON();
      statusCB1 = false;
      statusWait = false;
      
    }
  }
  if (statusWait == false) {
    if (millis() - startROT >= Mililit) {
      ROT_OFF();
      Turntable_On();
    }
  }
  if (Giay <= 9) {
    lcd.setCursor(17, 3);
    lcd.print("0");
    lcd.setCursor(18, 3);
    lcd.print(Giay);
  }
  if (Giay > 9 and Giay <= 60) {
    lcd.setCursor(17, 3);
    lcd.print(Giay);
  }

  if (Phut <= 9) {
    lcd.setCursor(14, 3);
    lcd.print("0");
    lcd.setCursor(15, 3);
    lcd.print(Phut);
  }
  if (Phut > 9 and Phut <= 60) {
    lcd.setCursor(14, 3);
    lcd.print(Phut);
  }

  if (Gio <= 9) {
    lcd.setCursor(11, 3);
    lcd.print("0");
    lcd.setCursor(12, 3);
    lcd.print(Gio);
  }

  lcd.setCursor(13, 3);
  lcd.print(":");
  lcd.setCursor(16, 3);
  lcd.print(":");
  thoigian = millis();
  // bắt đầu rót
  /*
    if (thoigian - hientai >= timecho) { // Thời gian cảm biến nhận chỉnh lại khi có bàn xoay
    hientai = thoigian;
    GiaTriCamBien = digitalRead(CB1);    // KHI CO VAT -> LOW
    if (GiaTriCamBien == LOW)
      thoigianQK = thoigian;
    digitalWrite(Relay_Bom, HIGH);
    Serial.println("Rot");
    }
  */
  // rót đầy
}

void Power() {
  digitalWrite(Relay_Power, HIGH);  // kich muc cao
}
void Start() {
  digitalWrite(Relay_Start, HIGH);
}
void Stop() {
  digitalWrite(Relay_Stop, HIGH);
}
// Băng tải 1
void Conveyor1_On() {
  digitalWrite(Relay_Conveyor1, HIGH);
}
void Conveyor1_Off() {
  digitalWrite(Relay_Conveyor1, LOW);
}
void Conveyor2_On() {
  digitalWrite(Relay_Conveyor2, HIGH);
}
void Conveyor2_Off() {
  digitalWrite(Relay_Conveyor1, LOW);
}
void Bat_Rot() {
  digitalWrite(Relay_Rot, HIGH);
}
void Tat_Rot() {
  digitalWrite(Relay_Rot, LOW);
}
void Turntable_On() {
  digitalWrite(Relay_Turntable, HIGH);
}
void Turntable_Off() {
  digitalWrite(Relay_Turntable, LOW);
}
void Calc(int GiaTriTheTichVoid) {
  if (GiaTriTheTichVoid <= 9) {
    HT1SO();
  } else if (GiaTriTheTichVoid > 9 & GiaTriTheTichVoid <= 99) {
    HT2SO();
  } else if (GiaTriTheTichVoid > 99 & GiaTriTheTichVoid <= 999) {
    HT3SO();
  }


  if (so_luong <= 9) {
    HT1SO_SL();
  } else if (so_luong > 9 & so_luong <= 99) {
    HT2SO_SL();
  } else if (so_luong > 99 & so_luong <= 999) {
    HT3SO_SL();
  }


  if (So_Luong_Con_Lai <= 9) {
    HT1SO_SLCL();
  } else if (So_Luong_Con_Lai > 9 & So_Luong_Con_Lai <= 99) {
    HT2SO_SLCL();
  } else if (So_Luong_Con_Lai > 99 & So_Luong_Con_Lai <= 999) {
    HT3SO_SLCL();
  }
}

void HT1SO() {
  lcd.setCursor(10, 0);
  lcd.print("    ");
  lcd.setCursor(14, 0);
  lcd.print(GiaTriTheTich);
  lcd.setCursor(16, 0);
  lcd.print("Ml");
}
void HT2SO() {
  lcd.setCursor(10, 0);
  lcd.print("   ");
  lcd.setCursor(13, 0);
  lcd.print(GiaTriTheTich);
  lcd.setCursor(16, 0);
  lcd.print("Ml");
}

void HT3SO() {

  lcd.setCursor(12, 0);
  lcd.print(GiaTriTheTich);
  lcd.setCursor(16, 0);
  lcd.print("Ml");
}

void HT1SO_SL() {
  lcd.setCursor(10, 1);
  lcd.print("    ");
  lcd.setCursor(14, 1);
  lcd.print(so_luong);
}
void HT2SO_SL() {
  lcd.setCursor(10, 1);
  lcd.print("   ");
  lcd.setCursor(13, 1);
  lcd.print(so_luong);
}

void HT3SO_SL() {
  lcd.setCursor(10, 1);
  lcd.print("  ");
  lcd.setCursor(12, 1);
  lcd.print(so_luong);
}

void HT1SO_SLCL() {
  lcd.setCursor(10, 2);
  lcd.print("    ");
  lcd.setCursor(14, 2);
  lcd.print(So_Luong_Con_Lai);
}
void HT2SO_SLCL() {
  lcd.setCursor(10, 2);
  lcd.print("   ");
  lcd.setCursor(13, 2);
  lcd.print(So_Luong_Con_Lai);
}
void HT3SO_SLCL() {
  lcd.setCursor(10, 2);
  lcd.print("  ");
  lcd.setCursor(12, 2);
  lcd.print(So_Luong_Con_Lai);
}
void ROT_ON() {
  digitalWrite(Relay_Bom, HIGH);
}
void ROT_OFF() {
  digitalWrite(Relay_Bom, LOW);
}