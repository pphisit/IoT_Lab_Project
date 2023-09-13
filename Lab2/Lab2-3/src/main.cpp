//3.LED 2 ดวงติดดับสลับกันโดยให้ ปุ่มกด 2 ปุ่ม เพิ่มและลดความเร็วการกระพริบ โดยกด 1 ครั้งจะเพิ่มและลดความเร็ว 
//ทีล่ะ 100 มิลลิวินาที ถ้าลดมากเกิน 1000 มิลลิวินาที ให้กลับมาเริ่มต้นที่ 100 มิลลิวินาที และถ้าเพิ่มต่ำกว่า 100 มิลลิวินาที 
//ให้กลับมาเริ่มต้นที่ 1000 มิลลิวินาที

#include <Arduino.h>

const int ledPin1 = D1;  // ขา LED 1
const int ledPin2 = D2;  // ขา LED 2
const int button1Pin = D3;  // ขาปุ่ม 1
const int button2Pin = D4;  // ขาปุ่ม 2

unsigned long previousMillis = 0;
unsigned long interval = 100;  // ความหน่วงเริ่มต้น 100 มิลลิวินาที
int ledState1 = LOW;
int ledState2 = HIGH;
unsigned long currentMillis;

enum State { LED1_ON, LED2_ON, WAIT_FOR_BUTTON_PRESS };
State currentState = LED1_ON;

void setup() {
  Serial.begin(115200);
  pinMode(ledPin1, OUTPUT);
  pinMode(ledPin2, OUTPUT);
  pinMode(button1Pin, INPUT_PULLUP);
  pinMode(button2Pin, INPUT_PULLUP);
}

void loop() {
  currentMillis = millis();

  switch (currentState) {
    case LED1_ON:
      if (currentMillis - previousMillis >= interval) {
        ledState1 = !ledState1;
        digitalWrite(ledPin1, ledState1);
        previousMillis = currentMillis;
      }
      if (digitalRead(button1Pin) == LOW) {
        currentState = WAIT_FOR_BUTTON_PRESS;
      }
      if (digitalRead(button2Pin) == LOW) {
        interval = min(1000, interval + 100);
      }
      break;

    case LED2_ON:
      if (currentMillis - previousMillis >= interval) {
        ledState2 = !ledState2;
        digitalWrite(ledPin2, ledState2);
        previousMillis = currentMillis;
      }
      if (digitalRead(button1Pin) == LOW) {
        currentState = WAIT_FOR_BUTTON_PRESS;
      }
      if (digitalRead(button2Pin) == LOW) {
        interval = max(100, interval - 100);
      }
      break;

    case WAIT_FOR_BUTTON_PRESS:
      if (digitalRead(button1Pin) == HIGH) {
        currentState = LED1_ON;
      }
      if (digitalRead(button2Pin) == HIGH) {
        currentState = LED2_ON;
      }
      break;
  }
}
