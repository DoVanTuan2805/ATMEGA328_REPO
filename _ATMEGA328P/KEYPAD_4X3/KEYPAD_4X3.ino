#include <Keypad.h>

//Bạn có thể tham khảo thêm tại: https://github.com/Chris--A/Keypad/blob/master/examples/HelloKeypad/HelloKeypad.ino

const byte rows = 4;     //số hàng
const byte columns = 3;  //số cột

int holdDelay = 700;  //Thời gian trễ để xem là nhấn 1 nút nhằm tránh nhiễu
int n = 3;            //
int state = 0;        //nếu state =0 ko nhấn,state =1 nhấn thời gian nhỏ , state = 2 nhấn giữ lâu
char key = 0;
// 2 - > 8
//Định nghĩa các giá trị trả về
char keys[rows][columns] = {
  { '1', '2', '3' },
  { '4', '5', '6' },
  { '7', '8', '9' },
  { '*', '0', '#' },
};

byte rowPins[rows] = { 8, 7, 6, 5 };  //Cách nối chân với Arduino
byte columnPins[columns] = { 4, 3, 2};

//cài đặt thư viện keypad
Keypad keypad = Keypad(makeKeymap(keys), rowPins, columnPins, rows, columns);
void setup() {
  Serial.begin(9600);  //bật serial, baudrate 9600
}
void loop() {
  char temp = keypad.getKey();
  if ((int)keypad.getState() == PRESSED) {
    if (temp != 0) {
      key = temp;
      Serial.println(key);
    }
  }

  
}