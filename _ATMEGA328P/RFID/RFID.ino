#include <SPI.h>
#include <MFRC522.h>

#define RST_PIN         0
#define SS_PIN          5

int UID[4], i;
LiquidCrystal_I2C lcd(0x27, 20, 4);
MFRC522 mfrc522(SS_PIN, RST_PIN);

void setup()
{
  Serial.begin(115200);
  SPI.begin();
  mfrc522.PCD_Init();
}

void loop()
{
  lcd.setCursor(0, 1);
  lcd.printf("UID:");
  if ( ! mfrc522.PICC_IsNewCardPresent())
  {
    return;
  }

  if ( ! mfrc522.PICC_ReadCardSerial())
  {
    return;
  }

  Serial.print("UID của thẻ: ");

  for (byte i = 0; i < mfrc522.uid.size; i++)
  {
    Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");
    UID[i] = mfrc522.uid.uidByte[i];
    Serial.print(UID[i], HEX);
    //delay(70);
  }

  Serial.println("   ");
  mfrc522.PICC_HaltA();         // TẠM NGỪNG ĐỌC
  mfrc522.PCD_StopCrypto1();    // NGỪNG ĐỌC VIỆC SỬ DỤNG RFID

}
