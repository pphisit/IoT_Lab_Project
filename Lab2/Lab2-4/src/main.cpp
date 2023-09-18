//4.กำหนดใช้ LED 4 ดวง มีปุ่มกด 2 ปุ่ม โดยปุ่มที่ 1 สามารถควบคุม LED ขยับไปทางขวา ส่วนปุ่มที่ 2 สามารถควบคุมขยับไปทางซ้าย เมื่อกด 1 ครั้ง โดย LED เริ่มต้นจะอยู่ซ้ายมือสุด     

#include <Arduino.h>

// กำหนดขาของ LED
const int ledPins[] = {D0, D1, D2, D3};
const int numLEDs = sizeof(ledPins) / sizeof(ledPins[0]);

// กำหนดขาของปุ่ม
const int buttonRightPin = D4;
const int buttonLeftPin = D5;

// กำหนดสถานะ
enum State {
  LEFTMOST,
  RIGHTMOST,
  MOVING_LEFT,
  MOVING_RIGHT
};

State currentState = LEFTMOST;

void setup() {
  // กำหนดขา LED เป็น OUTPUT
  for (int i = 0; i < numLEDs; i++) {
    pinMode(ledPins[i], OUTPUT);
    digitalWrite(ledPins[i], LOW);  // ปิด LED ทุกดวงเริ่มต้น
  }

  // กำหนดขาปุ่มเป็น INPUT_PULLUP
  pinMode(buttonRightPin, INPUT_PULLUP);
  pinMode(buttonLeftPin, INPUT_PULLUP);

  Serial.begin(115200);
}

void loop() {
  switch (currentState) {
    case LEFTMOST:
      digitalWrite(ledPins[0], HIGH);
      digitalWrite(ledPins[numLEDs - 1], LOW);
      if (digitalRead(buttonRightPin) == LOW) {
        currentState = MOVING_RIGHT;
        delay(100);  // ป้องกันการกระโดดสถานะ
      }
      break;

    case RIGHTMOST:
      digitalWrite(ledPins[numLEDs - 1], HIGH);
      digitalWrite(ledPins[0], LOW);
      if (digitalRead(buttonLeftPin) == LOW) {
        currentState = MOVING_LEFT;
        delay(100);
      }
      break;

    case MOVING_LEFT:
      digitalWrite(ledPins[numLEDs - 1], LOW);
      for (int i = 0; i < numLEDs - 1; i++) {
        digitalWrite(ledPins[i], HIGH);
        delay(200);
        digitalWrite(ledPins[i], LOW);
      }
      currentState = LEFTMOST;
      break;

    case MOVING_RIGHT:
      digitalWrite(ledPins[0], LOW);
      for (int i = numLEDs - 1; i > 0; i--) {
        digitalWrite(ledPins[i], HIGH);
        delay(200);
        digitalWrite(ledPins[i], LOW);
      }
      currentState = RIGHTMOST;
      break;
  }
}
