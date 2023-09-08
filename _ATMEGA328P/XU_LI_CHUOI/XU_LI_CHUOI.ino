String text = "1/2/3.4/11/52";
String t1, t2, t3, t4, t5;
String tach_chuoi(String text, String ki_tu, uint16_t vi_tri) {
  String tmp = text;
  for (int i = 0 ; i < vi_tri; i++) {
    tmp = tmp.substring(tmp.indexOf(ki_tu) + 1);
    if (tmp.indexOf(ki_tu) == -1 && i != vi_tri - 1) {       // neu ko tim thay ki tu (delim)tra ve -1
      return "";
    }
  }
  return tmp.substring(0, tmp.indexOf(ki_tu));
}
void setup() {
  Serial.begin(9600);
  Serial.println(text);
  t1 = splitString(text, "/", 1);
  Serial.println(t1);
  t2 = splitString(text, "/", 2);
  Serial.println(t2);
  t3 = splitString(text, "/", 3);
  Serial.println(t3);
  t4 = splitString(text, "/", 4);
  Serial.println(t4);
}

void loop() {


}
