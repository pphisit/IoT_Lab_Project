//2.กดติดกดดับ LED แบบ Pull-Down โดยใช้ Interrupt และDebounce ช่วย
/*

#include <Arduino.h>

const int buttonPin = D1;  // ขาปุ่ม
const int ledPin = D2;     // ขา LED

volatile bool buttonPressed = false;
bool ledState = false;
bool lastButtonState = true;
unsigned long lastDebounceTime = 0;
unsigned long debounceDelay = 50;

enum State { LED_ON, LED_OFF };
State currentState = LED_OFF;

void buttonInterrupt() {
  if (millis() - lastDebounceTime > debounceDelay) {
    buttonPressed = true;
  }
}

void setup() {
  Serial.begin(115200);
  pinMode(buttonPin, INPUT_PULLUP);
  pinMode(ledPin, OUTPUT);
  attachInterrupt(digitalPinToInterrupt(buttonPin), buttonInterrupt, FALLING);
}

void loop() {
  switch (currentState) {
    case LED_ON:
      digitalWrite(ledPin, HIGH);
      if (buttonPressed) {
        currentState = LED_OFF;
        buttonPressed = false;
      }
      break;

    case LED_OFF:
      digitalWrite(ledPin, LOW);
      if (buttonPressed) {
        currentState = LED_ON;
        buttonPressed = false;
      }
      break;
  }
}
*/

#include <Arduino.h>

const int LED_ON = 0;  // ขาปุ่ม
const int LED_OFF = 1;     // ขา LED
int state;

volatile bool pressed = false;
//bool ledState = false;
//bool lastButtonState = true;
//unsigned long lastDebounceTime = 0;
//unsigned long debounceDelay = 50;

void pressed() {
  if (digitalRead(D1)==HIGH) {
    delay(50);
  }
}

void setup() {
  Serial.begin(115200);
  pinMode(D1, INPUT);
  pinMode(D2, OUTPUT);
  state = LED_ON;
  attachInterrupt(digitalPinToInterrupt(D1), pressed, RISING);
}

void loop() {
  switch (state) {
    case LED_ON:
      digitalWrite(D2, HIGH);
      Serial.println("LED ON");
      if (pressed) {
        state = LED_OFF;
      //  pressed = false;
      }
      break;

    case LED_OFF:
      digitalWrite(D2, LOW);
      Serial.println("LED OFF");
      if (pressed) {
        state = LED_ON;
       // pressed = false;
      }
      break;
  }
}
