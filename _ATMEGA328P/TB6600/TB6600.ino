#include <EEPROM.h>
#include <SPI.h>
#include <MFRC522.h>
#define SS_PIN 10
#define RST_PIN 9

#define DIR_PIN 6
#define STEP_PIN 7
#define EN_PIN 5



int position1, current_position, num_position, num_positions;
int posi_value;

struct pos {
  int pos1_2;
  int pos2_3;
  int pos3_4;
  int pos4_5;
  int pos5_6;
  int pos6_1;
};
pos position;

String tag_UID1 = "9396DA6";
String tag_UID2 = "134B80A6";
String tag_UID3 = "D376D4A6";
String tag_UID4 = "F35A6AA6";
String tag_UID5 = "D3944AA6";
String tag_UID6 = "A38883A5";
String tag_UID7 = "43F91FA8";
String tagID = "";

MFRC522 mfrc522(SS_PIN, RST_PIN);
void setup() {
  Serial.begin(9600);
  pinMode(DIR_PIN, OUTPUT);
  pinMode(STEP_PIN, OUTPUT);
  pinMode(EN_PIN, OUTPUT);
  SPI.begin();
  mfrc522.PCD_Init();
  position.pos1_2 = -22;
  position.pos2_3 = -22;
  position.pos3_4 = -25;
  position.pos4_5 = -18;
  position.pos5_6 = -18;
  position.pos6_1 = -25;
  //EEPROM.write(10, 255);
  // position1 = EEPROM.read(10);
  // Serial.println(position1);
  // rotateDeg(255 - position1, 0.05);
  position1 = 1;
  num_position = 1;
  current_position = position1;
}
int k = 1;
int t_prev;
bool check = 0;
unsigned int arr[7] = { 1, 1, 1, 1, 1, 1, 1 };
bool arr_num[7] = { 0, 0, 0, 0, 0, 0, 0 };
unsigned int arr_pos[7] = { 1, 1, 1, 1, 1, 1, 1 };
void loop() {
  if (millis() - t_prev >= 3000) {
    while (readID()) {
      while (k < 7) {
        delay(10);
        if (arr[k] == 0) {
          k++;
        } else {
          posi_value = k;
          Serial.print(" Posi :");
          Serial.print(posi_value);
          Serial.println();
          break;
        }
      }
      if (tagID == tag_UID1) {
        arr_num[1]++;
        if (arr_num[1] == 1) {
          if (arr[posi_value] == 1) {
            num_positions = posi_value;
            arr[posi_value] = 0;
            arr_pos[1] = posi_value;
            Serial.println("the 1");
            check = 1;
          }
        }
        if (arr_num[1] == 2) {
          num_positions = arr_pos[1];
          arr_num[1] = 0;
          check = 1;
        }
        Serial.print("arr_num[1] : ");
        Serial.print(arr_num[1]);
        Serial.println();
      }
      if (tagID == tag_UID2) {
        arr_num[2]++;
        if (arr_num[2] == 1) {
          if (arr[posi_value] == 1) {
            num_positions = posi_value;
            arr[posi_value] = 0;
            arr_pos[2] = posi_value;
            Serial.println("the 2");
            check = 1;
          }
        }
        if (arr_num[2] == 2) {
          num_positions = arr_pos[1];
          arr_num[2] = 0;
          check = 1;
        }
        Serial.print("arr_num[2] : ");
        Serial.print(arr_num[2]);
        Serial.println();
      }
      if (tagID == tag_UID3) {
        if (arr[posi_value] == 1) {
          num_positions = posi_value;  // vi tri 2
          arr[posi_value] = 0;
          Serial.println("the 3");
          check = 1;
        }
      } else if (tagID == tag_UID4) {
        if (arr[posi_value] == 1) {
          num_positions = posi_value;  // vi tri 2
          arr[posi_value] = 0;
          Serial.println("the 4");
          check = 1;
        }
      }
      if (tagID == tag_UID5) {
        if (arr[posi_value] == 1) {
          num_positions = posi_value;  // vi tri 2
          arr[posi_value] = 0;
          Serial.println("the 5");
          check = 1;
        }
      }
      if (tagID == tag_UID6) {
        if (arr[posi_value] == 1) {
          num_positions = posi_value;  // vi tri 2
          arr[posi_value] = 0;
          Serial.println("the 6");
          check = 1;
        }
      }
      // if (tagID == tag_UID7) {
      //   if (arr[posi_value] == 1) {
      //     num_positions = posi_value;  // vi tri 2
      //     arr[posi_value] = 0;
      //     Serial.println("the 4");
      //     check = 1;
      //   }
      // }
      if (check == 1) {
        Serial.print("Mang : ");
        for (int f = 1; f < 7; f++) {
          Serial.print(arr[f]);
        }
        Serial.println();
        Serial.print("Begin : ");
        Serial.print(current_position);
        Serial.println();
        Serial.print("End : ");
        Serial.println(num_positions);
        runStep(current_position, num_position);
        Serial.println("Da chay xong Step !");
        current_position = num_positions;
        check = 0;
      }
    }
    t_prev = millis();
  }
}
void runStep(int begin, int end) {
  int deg_value;
  bool dir;
  int num[6] = { 0, 0, 0, 0, 0, 0 };
  if (begin < end) {  // chhieu thuan
    Serial.println("NUM CW !");
    dir = 0;
    for (int i = begin; i < end; i++) {
      num[i] = 1;
    }
  }
  // if (begin > end) {  // chieu nguoc
  //   dir = 1;
  //   Serial.println("NUM CCW !");
  //   for (int f = begin; f >= end; f--) {
  //     num[f] = 1;
  //   }
  // }
  if (num[1] == 1) {
    position.pos1_2 = -22;
  }
  if (num[1] == 0) {
    position.pos1_2 = 0;
  }
  if (num[2] == 1) {
    position.pos2_3 = -22;
  }
  if (num[2] == 0) {
    position.pos2_3 = 0;
  }
  if (num[3] == 1) {
    position.pos3_4 = -25;
  }
  if (num[3] == 0) {
    position.pos3_4 = 0;
  }
  if (num[4] == 1) {
    position.pos4_5 = -18;
  }
  if (num[4] == 0) {
    position.pos4_5 = 0;
  }
  if (num[5] == 1) {
    position.pos5_6 = -18;
  }
  if (num[5] == 0) {
    position.pos5_6 = 0;
  }
  if (dir == 0) {
    deg_value = position.pos1_2 + position.pos2_3 + position.pos3_4 + position.pos4_5 + position.pos5_6;
  }
  if (dir == 1) {
    deg_value = -(position.pos1_2 + position.pos2_3 + position.pos3_4 + position.pos4_5 + position.pos5_6);
  }
  rotateDeg(deg_value, 0.05);
  // for (int l = 1; l < 7; l++) {
  //   Serial.print(num[l]);
  // }
  // Serial.println();
  // Serial.print("Angle : ");
  // Serial.print(deg_value);
  // Serial.println();
}

void rotate(int steps, float speed) {
  //rotate a specific number of microsteps (8 microsteps per step) - (negitive for reverse movement)
  //speed is any number from .01 -> 1 with 1 being fastest - Slower is stronger
  int dir = (steps > 0) ? HIGH : LOW;
  steps = abs(steps);

  digitalWrite(DIR_PIN, dir);

  float usDelay = (1 / speed) * 70;

  for (int i = 0; i < steps; i++) {
    digitalWrite(STEP_PIN, HIGH);
    delayMicroseconds(usDelay);

    digitalWrite(STEP_PIN, LOW);
    delayMicroseconds(usDelay);
  }
}

void rotateDeg(float deg, float speed) {
  //rotate a specific number of degrees (negitive for reverse movement)
  //speed is any number from .01 -> 1 with 1 being fastest - Slower is stronger
  int dir = (deg > 0) ? HIGH : LOW;
  digitalWrite(DIR_PIN, dir);

  int steps = abs(deg) * (1 / 0.01);  //0.225
  float usDelay = (1 / speed) * 70;

  for (int i = 0; i < steps; i++) {
    digitalWrite(STEP_PIN, HIGH);
    delayMicroseconds(usDelay);

    digitalWrite(STEP_PIN, LOW);
    delayMicroseconds(usDelay);
  }
}
boolean readID() {
  //Check if a new tag is detected or not. If not return.
  if (!mfrc522.PICC_IsNewCardPresent()) {
    return false;
  }
  //Check if a new tag is readable or not. If not return.
  if (!mfrc522.PICC_ReadCardSerial()) {
    return false;
  }
  tagID = "";
  // Read the 4 byte UID
  for (uint8_t i = 0; i < 4; i++) {
    //readCard[i] = mfrc522.uid.uidByte[i];
    tagID.concat(String(mfrc522.uid.uidByte[i], HEX));  // Convert the UID to a single String
  }
  tagID.toUpperCase();
  mfrc522.PICC_HaltA();  // Stop reading
  return true;
}