// void ISR_Up() {
//   if (count < countLed) {
//     Serial.println("Press Up");
//     count++;
//   }
//   checkPress = true;
//   timePressList = millis();
// }
// void ISR_Down() {
//   if (count > 0) {
//     Serial.println("Press Down");
//     count--;
//   }
//   checkPress = true;
//   timePressList = millis();
// }
void init_LED() {
  pinMode(LED_VANG, INPUT_PULLUP);
  pinMode(LED_DO, INPUT_PULLUP);
  pinMode(LED_XANH, INPUT_PULLUP);
}

void init_BT() {
  pinMode(BT_UP, INPUT_PULLUP);
  pinMode(BT_DOWN, INPUT_PULLUP);
  pinMode(BT_NEXT, INPUT_PULLUP);
  // attachInterrupt(digitalPinToInterrupt(BT_UP), ISR_Up, FALLING);
  // attachInterrupt(digitalPinToInterrupt(BT_DOWN), ISR_Down, FALLING);
}

void init_SD() {
  if (!SD.begin(10)) {
    Serial.println("Card failed, or not present");
    // don't do anything more:
    while (1)
      ;
  }

  if (SD.exists(filename)) {
    SD.remove(filename);
    Serial.print("Delete File : ");
    Serial.print(filename);
    Serial.println();
  }
  if (SD.exists(filename1)) {
    SD.remove(filename1);
    Serial.print("Delete File : ");
    Serial.print(filename1);
    Serial.println();
  }
  if (SD.exists(filename2)) {
    SD.remove(filename2);
    Serial.print("Delete File : ");
    Serial.print(filename2);
    Serial.println();
  }
  if (SD.exists(filename3)) {
    SD.remove(filename3);
    Serial.print("Delete File : ");
    Serial.print(filename3);
    Serial.println();
  }

  txtFile = SD.open(filename, FILE_WRITE);
  delay(10);
  if (txtFile) {
    Serial.println("File Success");
    delay(10);
    txtFile.close();
  } else {
    Serial.println("ERROR OPEN FILE");
  }

  yellowFile = SD.open(filename1, FILE_WRITE);
  delay(10);
  if (yellowFile) {
    Serial.println("File Success");
    delay(10);
    yellowFile.close();
  } else {
    Serial.println("ERROR OPEN FILE");
  }

  blueFile = SD.open(filename2, FILE_WRITE);
  delay(10);
  if (blueFile) {
    Serial.println("File Success");
    delay(10);
    blueFile.close();
  } else {
    Serial.println("ERROR OPEN FILE");
  }

  redFile = SD.open(filename3, FILE_WRITE);
  delay(10);
  if (redFile) {
    Serial.println("File Success");
    delay(10);
    redFile.close();
  } else {
    Serial.println("ERROR OPEN FILE");
  }
}
