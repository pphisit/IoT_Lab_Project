//1.กดปุ่มกดดับปล่อยดิด LED แบบ Pull-Down โดยใช้ Interrupt และ Debounce

#include <Arduino.h>

// กำหนดขา GPIO ที่เชื่อมกับ LED
const int ledPin = D2;

// กำหนดขา GPIO ที่เชื่อมกับปุ่ม
const int buttonPin = D1;

// กำหนดตัวแปรสำหรับ State Machine
enum State { LED_OFF, LED_ON};
State currentState = LED_ON;


IRAM_ATTR void ButtonPress() {
  
  // ในฟังชั่นนี้จะถูกเรียกเมื่อเกิดการกดปุ่ม
  if (digitalRead(buttonPin)==HIGH) {
  //while (digitalRead(buttonPin) == HIGH)
  //    {          
   //     } 
    delay(100);
    Serial.println("Button Pressed");
    // ตรวจสอบ Debounce โดยรอเวลา debounceDelay
   //    
      currentState = LED_OFF;
    }    
}

void setup() {
  // เริ่มต้น Serial Monitor
  Serial.begin(115200);
  // กำหนดขาที่เชื่อมกับ LED เป็น OUTPUT
  pinMode(ledPin, OUTPUT);
  //digitalWrite(ledPin, LOW);
  // กำหนดขาที่เชื่อมกับปุ่มเป็น INPUT_PULLUP
  pinMode(buttonPin, INPUT);
  // กำหนดให้ฟังชั่น ButtonPress เรียกใช้งานเมื่อเกิดการกดปุ่ม
  attachInterrupt(digitalPinToInterrupt(buttonPin), ButtonPress, RISING);
}

void loop() {
  switch (currentState) {
    case LED_OFF:
    Serial.println("LED OFF");
      digitalWrite(ledPin, LOW);
      if(digitalRead(buttonPin)==LOW){
       currentState = LED_ON;   
      }         
      break;
    case LED_ON:
      Serial.println("LED ON");
      digitalWrite(ledPin, HIGH);     
      break;
  }
}




