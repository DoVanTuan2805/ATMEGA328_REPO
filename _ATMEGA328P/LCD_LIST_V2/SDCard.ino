#define dataInLine 23

void writeDataSD(int8_t d, int8_t mont, int8_t h, int8_t m, int8_t s, LED_COLOR_t color) {
  countLed++;
  count = countLed;
  char data[100];
  String color_c;
  memset(data, 0, sizeof(data));
  if (color == RED) {
    sprintf(data, "%6ld %2d/%2d %2d:%2d DO", countLed, d, mont, h, m);
    redFile = SD.open(filename3, FILE_WRITE);
    delay(10);
    if (redFile) {
      txtFile.println(data);
      Serial.println("File Red Success");
      delay(10);
      redFile.close();
    } else {
      Serial.println("ERROR OPEN Red FILE");
    }
  } else if (color == YELLOW) {
    sprintf(data, "%6ld %2d/%2d %2d:%2d VA", countLed, d, mont, h, m);
    yellowFile = SD.open(filename1, FILE_WRITE);
    delay(10);
    if (yellowFile) {
      yellowFile.println(data);
      Serial.println("File Yellow Success");
      delay(10);
      yellowFile.close();
    } else {
      Serial.println("ERROR OPEN Yellow FILE");
    }
  } else if (color == BLUE) {
    sprintf(data, "%6ld %2d/%2d %2d:%2d XA", countLed, d, mont, h, m);
    blueFile = SD.open(filename2, FILE_WRITE);
    delay(10);
    if (blueFile) {
      blueFile.println(data);
      Serial.println("File Blue Success");
      delay(10);
      blueFile.close();
    } else {
      Serial.println("ERROR OPEN Blue FILE");
    }
  }
  // Serial.println(strlen(data) - 5);
  Serial.println(data);

  txtFile = SD.open(filename, FILE_WRITE);
  if (txtFile) {
    txtFile.println(data);
    Serial.println("File Data Success");
    txtFile.close();

  } else {
    Serial.println("ERROR OPEN Data FILE");
  }
}

String dataRead;
void readDataSD(char *buffer, int line) {
  char buff[23];
  String lista;
  memset(buff, 0, sizeof(buff));
  lista = "";

  txtFile = SD.open(filename);
  if (txtFile) {
    txtFile.seek(line * dataInLine);
    lista = txtFile.readStringUntil('\n');
    // Serial.print("lista :");
    // Serial.print(lista);
    // Serial.println();
    lista.toCharArray(buff, sizeof(buff));
    strncpy(buffer, buff + 7, 14);
    // Serial.print("buff2 :");
    // Serial.print(buff2);
    // Serial.println();
    txtFile.close();
  } else {
    Serial.println("error opening test.txt");
  }
}
