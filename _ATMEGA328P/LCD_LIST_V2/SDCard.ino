#define dataInLine 23

void writeDataSD(int8_t d, int8_t mont, int8_t h, int8_t m, int8_t s, LED_COLOR_t color) {
  countLed++;
  count = countLed;
  char data[100];
  String color_c;
  memset(data, 0, sizeof(data));
  if (color == RED) {
    sprintf(data, "%6ld %2d/%2d %2d:%2d DO", countLed, d, mont, h, m);
  } else if (color == YELLOW) {
    sprintf(data, "%6ld %2d/%2d %2d:%2d VA", countLed, d, mont, h, m);
  } else if (color == BLUE) {
    sprintf(data, "%6ld %2d/%2d %2d:%2d XA", countLed, d, mont, h, m);
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
