//2.กดติดกดดับ LED แบบ Pull-Down โดยใช้ Interrupt และDebounce ช่วย
//1.กดปุ่มกดดับปล่อยดิด LED แบบ Pull-Down โดยใช้ Interrupt และ Debounce
/*
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
*/
#include <Arduino.h>

// กำหนดขา GPIO ที่เชื่อมกับ LED
const int ledPin = D2;

// กำหนดขา GPIO ที่เชื่อมกับปุ่ม
const int buttonPin = D1;

// กำหนดตัวแปรสำหรับ State Machine
enum State { LED_OFF, LED_ON, WAIT_FOR_RELEASE };
State currentState = LED_OFF;

// กำหนดตัวแปรสำหรับเก็บค่าปุ่มขณะกดและปล่อย
volatile bool buttonPressed = false;

IRAM_ATTR void handleButtonPress() {
  // ในฟังชั่นนี้จะถูกเรียกเมื่อเกิดการกดปุ่ม
  if (!buttonPressed) {
    // ตรวจสอบ Debounce โดยรอเวลา debounceDelay
    delay(50);
    if (digitalRead(buttonPin) == HIGH) {
      buttonPressed = true;
    }
  }
}
void setup() {
  // เริ่มต้น Serial Monitor
  Serial.begin(115200);

  // กำหนดขาที่เชื่อมกับ LED เป็น OUTPUT
  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, LOW);

  // กำหนดขาที่เชื่อมกับปุ่มเป็น INPUT_PULLUP
  pinMode(buttonPin, INPUT);


  // กำหนดให้ฟังชั่น handleButtonPress เรียกใช้งานเมื่อเกิดการกดปุ่ม
  attachInterrupt(digitalPinToInterrupt(buttonPin), handleButtonPress, FALLING);
}

void loop() {
  switch (currentState) {
    case LED_OFF:
      digitalWrite(ledPin, LOW);
      if (buttonPressed) {
        currentState = LED_ON;
      }
      break;



    case LED_ON:
      digitalWrite(ledPin, HIGH);
      if (buttonPressed) {
        currentState = LED_OFF;
      }
      break;
  }
}


