const int BUTTON_PIN = 5;           
const int SHORT_PRESS_TIME = 1000;  
const int LONG_PRESS_TIME = 1000;  


int lastState = LOW;  
int currentState;     
unsigned long pressedTime = 0;
unsigned long releasedTime = 0;
bool isPressing = false;
bool isLongDetected = false;

void setup() {
  Serial.begin(9600);
  pinMode(BUTTON_PIN, INPUT_PULLUP);
  Serial.println("Xin chao");
}

void loop() {
  currentState = digitalRead(BUTTON_PIN);

  if (lastState == HIGH && currentState == LOW) {  // button is pressed
    pressedTime = millis();
    isPressing = true;
    isLongDetected = false;
  } else if (lastState == LOW && currentState == HIGH) {  // button is released
    isPressing = false;
    releasedTime = millis();
    isLongDetected = true;
    long pressDuration = releasedTime - pressedTime;

    if (pressDuration > 100 && pressDuration < SHORT_PRESS_TIME )
      Serial.println("A short press is detected");
  }
  if (isPressing == true && isLongDetected == false) {
    long pressDuration = millis() - pressedTime;
    if (pressDuration > 1000 && pressDuration < 2000) {
      Serial.println("1");
    }
    if (pressDuration > 2000 && pressDuration < 3000) {
      Serial.println("2");

    }
    if (pressDuration > 3000) {
      Serial.println("3");

    }
  }
  lastState = currentState;
}