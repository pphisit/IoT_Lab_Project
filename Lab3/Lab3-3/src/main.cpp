// 3.	ใช้ตัวต้านทานปรับค่าได้ คุมทิศทางของมอเตอร์ ผ่าน
//(ถ้าค่าตัวต้านทาน0-124 มอเตอร์จะหมุนตามเข็ม และค่า 125-255 มอเตอร์จะหมุนทางซ้าย)
#include <Arduino.h>

// กำหนดขา GPIO ที่เชื่อมกับมอเตอร์
const int CLOCKWISE = 0; // สำหรับควบคุมทิศทางการหมุน
const int ANTI_CLOCKWISE = 1; // สำหรับควบคุมทิศทางการหมุน
const int motorPin1 = D5; // สำหรับควบคุมทิศทางการหมุน
const int motorPin2 = D6; // สำหรับควบคุมทิศทางการหมุน
int state ;
// กำหนดขา GPIO ที่เชื่อมกับตัวต้านทาน
//const int potentiometerPin = A0;

void setup() {
  // เริ่มต้น Serial Monitor
  Serial.begin(115200);

  // กำหนดขาที่เชื่อมกับมอเตอร์เป็น OUTPUT
  pinMode(motorPin1, OUTPUT);
  pinMode(motorPin2, OUTPUT);
  pinMode(A0, INPUT);
  
  // กำหนดขาที่เชื่อมกับตัวต้านทานเป็น INPUT
 
  state = CLOCKWISE;
}

void loop() {
  int potValue = analogRead(A0);
  int motorSpeed = map(potValue, 0, 1023, 0, 255);
  Serial.println(motorSpeed);

  switch (state) {
    case CLOCKWISE:
      analogWrite(motorPin1, 50);
      analogWrite(motorPin2, 0);
      if (motorSpeed >= 125) {
        state = ANTI_CLOCKWISE;
      }
      break;

    case ANTI_CLOCKWISE:
      analogWrite(motorPin1, 0);
      analogWrite(motorPin2, 50);
      if (motorSpeed < 125) {
        state = CLOCKWISE;
      }
      break;
  }
}
