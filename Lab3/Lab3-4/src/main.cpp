//ผ่าน
#include <Arduino.h>

// กำหนดขา GPIO ที่เชื่อมกับมอเตอร์

const int motorPin1 = D5; // สำหรับควบคุมทิศทางการหมุน
const int motorPin2 = D6; // สำหรับควบคุมทิศทางการหมุน


//const int pwmPin = 14;   // สำหรับควบคุมความเร็ว PWM
int motorSpeed ;
// กำหนดขา GPIO ที่เชื่อมกับปุ่ม
const int buttonPin = D1;

// กำหนดตัวแปรสำหรับ State Machine
enum State { STOPPED, clockwise, anticlockwise };
State currentState = clockwise; 


void setup() {
  // เริ่มต้น Serial Monitor
  Serial.begin(115200);

  // กำหนดขาที่เชื่อมกับมอเตอร์เป็น OUTPUT
  pinMode(motorPin1, OUTPUT);
  pinMode(motorPin2, OUTPUT);
  pinMode(A0, INPUT);
  // กำหนดขา PWM เป็น OUTPUT
  //pinMode(pwmPin, OUTPUT);

  // กำหนดขาที่เชื่อมกับปุ่มเป็น INPUT_PULLUP
  pinMode(buttonPin, INPUT);

}

void loop() {

  switch (currentState) {

    case clockwise:
      motorSpeed =map(analogRead(A0),0,1023,0,255);
      Serial.println("clockwise  "+ String(motorSpeed));
      //analogWrite(, 255); // เพิ่มความเร็วของ PWM
      analogWrite(motorPin1, motorSpeed); // ทิศทางการหมุนข้างหน้า
      analogWrite(motorPin2, LOW);
      if (digitalRead(buttonPin) == HIGH) {
        while (digitalRead(buttonPin) == HIGH)
        {
        }
        currentState = anticlockwise; // ถ้าปุ่มถูกกด สั่งให้มอเตอร์หมุนข้างหลัง
      }
      break;

    case anticlockwise:
      //analogWrite(pwmPin, 255); // เพิ่มความเร็วของ PWM
      motorSpeed =map(analogRead(A0),0,1023,0,255);
      Serial.println("anticlockwise  "+ String(motorSpeed));
      analogWrite(motorPin1, LOW); // ทิศทางการหมุนข้างหลัง
      analogWrite(motorPin2, motorSpeed);
      if (digitalRead(buttonPin) == HIGH) {
        while (digitalRead(buttonPin) == HIGH)
        {
        }
        
        currentState = clockwise; // ถ้าปุ่มถูกกด สั่งให้มอเตอร์หยุดหมุน
      }
      break;
  }
}
