/*
shiftOut ra 1 Module LED 7 đoạn đơn
*/
//chân ST_CP của 74HC595
int ST = 8;
//chân SH_CP của 74HC595
int SH = 12;
//Chân DS của 74HC595
int DS = 11;
 
// Ta sẽ xây dựng mảng hằng số với các giá trị cho trước
// Các bit được đánh số thứ tự (0-7) từ phải qua trái (tương ứng với A-F,DP)
// Vì ta dùng LED 7 đoạn chung cực dương nên với các bit 0
// thì các đoạn của LED 7 đoạn sẽ sáng
// với các bit 1 thì đoạn ấy sẽ tắt
 
//mảng có 10 số (từ 0-9) và 
const byte Seg[10] = {
  ​0b11000000,//0 - các thanh từ a-f sán
  ​0b11111001,//1 - chỉ có 2 thanh b,c sán
  ​0b10100100,//
  ​0b10110000,//
  ​0b10011001,//
  ​0b10010010,//
  ​0b10000010,//
  ​0b11111000,//
  ​0b10000000,//
  ​0b10010000,//
};
 
 
void setup() {
  ​//Bạn BUỘC PHẢI pinMode các chân này là OUTPU
  ​pinMode(ST, OUTPUT);
  ​pinMode(SH, OUTPUT);
  ​pinMode(DS, OUTPUT);
}
 
void HienThiLED7doan(unsigned long Giatri, byte SoLed = 2) {
  
  ​byte *array= new byte[SoLed]
  ​for (byte i = 0; i < SoLed; i++) 
    ​//Lấy các chữ số từ phải quá trá
    {
    ​array[i] = (byte)(Giatri % 10UL);
    ​Giatri = (unsigned long)(Giatri /10UL);
  ​}
  ​digitalWrite(ST, LOW)
  ​for (int i = SoLed - 1; i >= 0; i--)
  {
    ​shiftOut(DS, SH, MSBFIRST, Seg[array[i]]);
  }
  ​digitalWrite(ST, HIGH);
  ​free(array);
}
 
 
void loop() { 
  ​static unsigned long point = 0;
  
  ​HienThiLED7doan(point, 2);
  
  ​point = (point + 1) % 100UL; // Vòng tuần hoàn từ 0--9
  ​delay(500);  //Đợi 0.5 s cho mỗi lần tăng s
}
