//2.กดติดกดดับ LED แบบ Pull-Down โดยใช้ Interrupt และDebounce ช่วย

#include <Arduino.h>

// กำหนดขา GPIO ที่เชื่อมกับ LED
const int ledPin = D2;

// กำหนดขา GPIO ที่เชื่อมกับปุ่ม
const int buttonPin = D1;

// กำหนดตัวแปรสำหรับ State Machine
enum State { LED_OFF, LED_ON};
State currentState = LED_ON;


IRAM_ATTR void handleButtonPress() {
  //delay(100);
     while (digitalRead(buttonPin) == HIGH)
        {          
        }  
  // ในฟังชั่นนี้จะถูกเรียกเมื่อเกิดการกดปุ่ม
  if (currentState == LED_ON) {     
      currentState = LED_OFF;
    }    
    else if (currentState == LED_OFF)
    {
      currentState = LED_ON;
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


  // กำหนดให้ฟังชั่น handleButtonPress เรียกใช้งานเมื่อเกิดการกดปุ่ม
  attachInterrupt(digitalPinToInterrupt(buttonPin), handleButtonPress, RISING);
}

void loop() {
  switch (currentState) {
    case LED_OFF:
    Serial.println("LED OFF");
      digitalWrite(ledPin, LOW);    
      break;
    case LED_ON:
      Serial.println("LED ON");
      digitalWrite(ledPin, HIGH);   
      break;
  }
}




