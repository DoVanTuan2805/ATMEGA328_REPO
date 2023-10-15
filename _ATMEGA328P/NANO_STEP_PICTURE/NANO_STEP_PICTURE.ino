#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 16, 2);  // set the LCD address to 0x27 for a 16 chars and 2 line display

#define MS1 2
#define MS2 3
#define MS3 4

#define stepPin 5
#define dirPin 6

#define RL1 11
#define RL2 12

#define RUN 7
#define SET 8
#define UP 9
#define DOWN 10
#define CTHT A1

#define SHORT_TIME 50

#define ONE_MM 80

typedef struct {
  bool isPressing;
  bool isShortDetected;
  bool currState;
  bool prevState;
  uint64_t pressTime;
  uint64_t releaseTime;
} Button_t;
Button_t run, set, up, down, ctht;
bool page = 0;
uint8_t mode = 0;
float speed = 0.1;
uint16_t speedPicture = 1000; 

int Distance = 30;
int NOP = 90;
int NOP_process = 0;

bool interrupt_soft = 0;
bool goHome = 0;
bool goHomeComplete = false;
bool running = false;
bool runningBack = false;
float DistanceOfPicture;
uint16_t PictureRunned, NumDistance;
uint64_t timeRelay;
bool takePictureComplete = false;
uint8_t countRelay = 0;
void initModule() {
  pinMode(stepPin, OUTPUT);
  pinMode(dirPin, OUTPUT);

  pinMode(MS1, OUTPUT);
  pinMode(MS2, OUTPUT);
  pinMode(MS3, OUTPUT);

  digitalWrite(MS1, HIGH);
  digitalWrite(MS2, HIGH);
  digitalWrite(MS3, HIGH);

  pinMode(RL1, OUTPUT);
  pinMode(RL2, OUTPUT);

  pinMode(RUN, INPUT);
  pinMode(SET, INPUT);
  pinMode(UP, INPUT);
  pinMode(DOWN, INPUT);
  pinMode(CTHT, INPUT);

  lcd.init();
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("xin chao");

  run.currState = HIGH;
  run.prevState = HIGH;

  set.currState = HIGH;
  set.prevState = HIGH;

  up.currState = HIGH;
  up.prevState = HIGH;

  down.currState = HIGH;
  down.prevState = HIGH;

  ctht.currState = HIGH;
  ctht.prevState = HIGH;
}
void setup() {
  Serial.begin(9600);
  initModule();
  //Changes the rotations direction
  //rotate(3200, 0.5);          // 3200 = 40 mm GT20
}
void loop() {
  if (goHome == true) {
    goHomeComplete = false;
    while (true) {
      if (interrupt_soft == 1) {
        goHome = false;
        goHomeComplete = true;
        break;
      }
      digitalWrite(dirPin, LOW);
      rotate_CTHT(3200, 0.2);
    }
  }

  checkButton(&ctht, CTHT);
  checkButton(&run, RUN);
  checkButton(&set, SET);
  checkButton(&up, UP);
  checkButton(&down, DOWN);

  mainLcd(page, mode);
  if (running == true) {
    digitalWrite(dirPin, HIGH);
    DistanceOfPicture = float(Distance) / float(NOP);
    PictureRunned = NOP;
    Serial.println(DistanceOfPicture);
    lcd.clear();
    while (true) {
      checkButton(&set, SET);
      if (runningBack == true) {
        digitalWrite(RL1, LOW);
        digitalWrite(RL2, LOW);
        runningBack = false;
        goHomeComplete = false;
        running = false;
        page = 0;
        mode = 0;
        break;
      }
      NOP_process = NOP - PictureRunned;
      if (takePictureComplete == true) {  // take of picture complete
        PictureRunned--;
        Serial.print("DistanceOfPicture :");
        Serial.print(DistanceOfPicture * ONE_MM);
        Serial.println();
        rotate_Picture(DistanceOfPicture * ONE_MM, speed);
      } else {
        if (millis() - timeRelay >= speedPicture) {
          processLCD();
          countRelay++;
          if (countRelay == 1) {
            digitalWrite(RL1, HIGH);
          } else if (countRelay == 2) {
            digitalWrite(RL2, HIGH);
          } else if (countRelay == 3) {
            digitalWrite(RL1, LOW);
            digitalWrite(RL2, LOW);
          } else if (countRelay == 4) {
            countRelay = 0;
            takePictureComplete = true;
          }
          timeRelay = millis();
        }
      }
      if (PictureRunned == 0) {
        Serial.println("Break");
        goHomeComplete = false;
        running = false;
        page = 0;
        mode = 0;
        lcd.clear();
        break;
      }
    }
  }
}
