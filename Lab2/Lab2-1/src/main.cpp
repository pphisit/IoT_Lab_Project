//1.กดปุ่มกดดับปล่อยดิด LED แบบ Pull-Down โดยใช้ Interrupt และ Debounce

#include <Arduino.h>

const int LED_ON = 0;  
const int LED_OFF = 1; 
int state;

volatile bool buttonState = false;
bool lastButtonState = false;

IRAM_ATTR void buttonInterrupt() {
  buttonState = true;
}

void setup() {
  pinMode(D1, INPUT);
  pinMode(D2, OUTPUT);
  attachInterrupt(digitalPinToInterrupt(D1), buttonInterrupt, FALLING);
  state = LED_ON;
}

void loop() {
  switch (state) {
    case LED_ON:
      digitalWrite(D2, HIGH);
      if (buttonState) {
        state = LED_OFF;
        buttonState = false;
      }
      break;

    case LED_OFF:
      digitalWrite(D2, LOW);
      if (!buttonState) {
        state = LED_ON;
        buttonState = false;
      }
      break;
  }
}
