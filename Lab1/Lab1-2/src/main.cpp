//2.	LED 2 ดวง ติด-ดับ สลับกัน

#include <Arduino.h>
// กำหนดขา GPIO ที่เชื่อมกับ LED
const int LED1_ON = 0;
const int LED2_ON = 1;
int state ;

void setup() {
  
  Serial.begin(115200);

  // กำหนดขาที่เชื่อมกับ LED เป็น OUTPUT
  pinMode(D0, OUTPUT);
  pinMode(D1, OUTPUT);
  digitalWrite(D0, LOW);
  digitalWrite(D1, LOW);
  
}

void loop() {
  switch (state) {
    case LED1_ON:
      digitalWrite(D0, HIGH);
      digitalWrite(D1, LOW);      
      delay(1000); // หน่วงเวลา 1 วินาที
      state = LED2_ON;
      break;
    case LED2_ON:
      digitalWrite(D0, LOW);
      digitalWrite(D1, HIGH);      
      delay(1000); // หน่วงเวลา 1 วินาที
      state = LED1_ON;
      break;
  }
}
/*
void loop() {
  if(state==LED1_ON){    
      digitalWrite(D0, HIGH);
      digitalWrite(D1, LOW);      
      delay(1000); // หน่วงเวลา 1 วินาที
      state = LED2_ON;      
  }
  else if(state==LED2_ON){   
      digitalWrite(D0, LOW);
      digitalWrite(D1, HIGH);      
      delay(1000); // หน่วงเวลา 1 วินาที
      state = LED1_ON;      
  }
}



#include <ESP8266WiFi.h>

// กำหนดขา GPIO ที่เชื่อมกับ LED
const int ledPin1 = 2;
const int ledPin2 = 3;

// กำหนดสถานะของ State Machine
enum State { LED1_ON, LED2_ON };
State currentState = LED1_ON;

void setup() {
  // เริ่มต้น Serial Monitor
  Serial.begin(115200);

  // กำหนดขาที่เชื่อมกับ LED เป็น OUTPUT
  pinMode(ledPin1, OUTPUT);
  pinMode(ledPin2, OUTPUT);
  digitalWrite(ledPin1, LOW);
  digitalWrite(ledPin2, LOW);
}

void loop() {
  switch (currentState) {
    case LED1_ON:
      digitalWrite(ledPin1, HIGH);
      digitalWrite(ledPin2, LOW);
      currentState = LED2_ON;
      delay(1000); // หน่วงเวลา 1 วินาที
      break;

    case LED2_ON:
      digitalWrite(ledPin1, LOW);
      digitalWrite(ledPin2, HIGH);
      currentState = LED1_ON;
      delay(1000); // หน่วงเวลา 1 วินาที
      break;
  }
}

*/