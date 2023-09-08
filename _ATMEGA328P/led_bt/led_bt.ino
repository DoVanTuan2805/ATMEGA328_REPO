const int btA = 5;
const int btB = 6;
#define led1 2
#define led2 3

#define l1(x) digitalWrite(led1, x)
#define l2(x) digitalWrite(led2, x)

unsigned long curr_time = 0, prev_time = 0;
int time_bt = 0, time_bts = 0, tt_bt = 0;
bool st_btA = 0, tt = 0, mode = 0;
void setup() {
  Serial.begin(9600);
  pinMode(btA, INPUT);
  pinMode(btB, INPUT);

  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  l1(1);
  l2(1);
  delay(500);
  l1(0);
  l2(0);
}

void loop() {
  st_btA = digitalRead(btA);
  if (digitalRead(btB) != 1) {    // 0
    tt = 0;                       // 0
    delay(50);
    while (digitalRead(btB) != 1) {
      if ((millis() - prev_time) > 2000) {      // 2s 
        prev_time = millis();
        tt = 1;
        if (time_bt >= 7) {
          time_bt = 7;            // 
          l2(1);
        }
        if (time_bt >= 4 && time_bt < 7) {
          time_bt = 4;
        }
        time_bt++;      // 2s  = + 1
        Serial.println(time_bt);
        if (time_bt >= 2 && time_bt < 5) {
          l2(1);
          delay(1000);
          l2(0);
        }
      }
    }
    l2(0);
    time_bts = time_bt;
    time_bt = 0;

    if (tt != 1) {
      mode = !mode;
    }
    delay(100);
  }

  if (mode != 1) {
    cd5(st_btA);
    Serial.print("che do 5");
    Serial.println();
  }
  if (mode != 0) {
    Serial.print("4 che do --");
    Serial.print(time_bts);
    Serial.println();
    switch (time_bts) {
      case 0:
        cd1(st_btA);
        break;
      case 1:
        cd1(st_btA);
        break;
      case 7:
        cd1(st_btA);
        break;
      case 2:
        cd2(st_btA);
        break;
      case 3:
        cd3(st_btA);
        break;
      case 4:
        cd4(st_btA);
        break;
      case 6:
        cd5(st_btA);
        break;
    }
  }
}
void cd1(bool tt) {
  if (tt != 0) {
    l1(0);
  } else {
    l1(1);
  }
}
void cd2(bool tt) {
  if (tt != 0) {
    l1(0);
  } else {
    l1(1);
    delay(100);
    l1(0);
    l1(1);
    delay(100);
    l1(0);
    l1(1);
    delay(100);
    l1(0);
    l1(1);
    delay(100);
    l1(0);
  }
}
void cd3(bool tt) {
  if (tt != 0) {
    l1(0);
  } else {
    for (int i = 0; i < 6; i++) {
      l1(1);
      delay(1000);
      l1(0);
    }
  }
}
void cd4(bool tt) {
  if (tt != 0) {
    l1(0);
  } else {
    for (int i = 0; i < 7; i++) {
      l1(1);
      delay(1000);
      l1(0);
    }
  }
}
void cd5(bool tt) {
  if (tt != 0) {
    l1(0);
  } else {
    for (int i = 0; i < 8; i++) {
      l1(1);
      delay(1000);
      l1(0);
    }
  }
}
