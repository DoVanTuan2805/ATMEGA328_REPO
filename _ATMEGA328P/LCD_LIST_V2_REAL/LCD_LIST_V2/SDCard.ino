#define dataInLine 25

void writeDataSD(int8_t d, int8_t mont, int8_t h, int8_t m, int8_t s, LED_COLOR_t color) {
  countLed++;
  count = countLed;
  char data[100];
  String color_c;
  memset(data, 0, sizeof(data));
  if (color == RED) {
    sprintf(data, "%6ld %2d/%2d %2d:%2d:%2d D", countLed, d, mont, h, m, s);
  } else if (color == YELLOW) {
    sprintf(data, "%6ld %2d/%2d %2d:%2d:%2d V", countLed, d, mont, h, m, s);
  } else if (color == BLUE) {
    sprintf(data, "%6ld %2d/%2d %2d:%2d:%2d X", countLed, d, mont, h, m, s);
  }
  // Serial.println(strlen(data) - 5);
  Serial.println(data);

  txtFile = SD.open(filename, FILE_WRITE);
  if (txtFile) {
    txtFile.println(data);
    Serial.println("Write File Success");
    txtFile.close();

  } else {
    Serial.println("ERROR OPEN FILE");
  }
}

String dataRead;
void readDataSD(char *buffer, int line) {
  char buff[30];
  String lista;
  memset(buff, 0, sizeof(buff));
  lista = "";

  txtFile = SD.open(filename);
  if (txtFile) {
    txtFile.seek(line * dataInLine);
    lista = txtFile.readStringUntil('\n');
    Serial.print("lista :");
    Serial.print(lista);
    Serial.println();
    lista.toCharArray(buff, sizeof(buff));
    Serial.print("buff :");
    Serial.print(buff);
    Serial.println();
    strncpy(buffer, buff + 7, 16);
    // Serial.print("buffer :");
    // Serial.print(buffer);
    // Serial.println();
    txtFile.close();
  } else {
    Serial.println("error opening test.txt");
  }
}
