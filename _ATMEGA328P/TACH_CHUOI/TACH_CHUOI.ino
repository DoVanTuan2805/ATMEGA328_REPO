String text = "50/20/40";       // length 8       vd: 50,20,40,

void setup() {
  Serial.begin(9600);
}

void loop() {
  int indexMax = text.length() - 1;   // 0-7
  char kitu = '/';
  int ki_tu_tim_thay = 0;
  int vi_tri_muon_tim = 1;
  int x_y[] = {0, -1};
  for (int i = 0; i <= indexMax ; i++) {
    if (text.charAt(i) == kitu || i == indexMax) { 
      x_y[0] = x_y[1] + 1;
      if (i == indexMax) {
        x_y[1] = i + 1;
      }
      else {
        x_y[1] = i;
      }
      ki_tu_tim_thay++;
      if (ki_tu_tim_thay > vi_tri_muon_tim)
      {
        break;
      }
//////////////////
    }
  }
  Serial.println(text.substring(x_y[0], x_y[1]));
  Serial.println();
}
