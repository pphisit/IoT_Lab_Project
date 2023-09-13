//1.	เปิด-ปิด LED ภายนอกโดยผ่าน Serial Monitor
#include <Arduino.h>
const int LED_ON = 0;
const int LED_OFF = 1;
int state ;

void setup() {
  state=LED_OFF;  
  Serial.begin(115200);  
  pinMode(D2, OUTPUT);
}

void loop() {
  // ตรวจสอบ Serial Monitor
  // Serial.print("Input: ");
  while (!Serial.available()){} //เมื่อไม่มีการพิมพ์ใดๆ บน Serial monitor จะทำงานวนใน Loop นี้

  char command =Serial.read(); //อ่านค่า String จากการพิมพ์ผ่าน Serial monitor โดยเก็บค่าที่อ่านได้ไว้ในตัวแปร input
  Serial.println(command); 

  switch (command) {
    case '1':    
      if (state == LED_OFF) {
        state = LED_ON;
        digitalWrite(D2, HIGH);
        Serial.println("เปิด LED");
      }
      break;
    case '0':
      if (state == LED_ON) {
        state = LED_OFF;
        digitalWrite(D2, LOW);
        Serial.println("ปิด LED");
      }
      break;
    default:
      Serial.println("คำสั่งไม่ถูกต้อง");
  }
}


/*#include <Arduino.h>
// กำหนดขา GPIO ที่เชื่อมกับ LED
const int ledPin = 2;

// กำหนดสถานะของ State Machine
enum State { OFF, ON };
State currentState = OFF;

void setup() {
  // เริ่มต้น Serial Monitor
  Serial.begin(115200);

  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, LOW);
}

void loop() {
  // ตรวจสอบ Serial Monitor
  if (Serial.available() > 0) {
    char command = Serial.read();
    handleCommand(command);
  }
}

void handleCommand(char command) {
  switch (command) {
    case '1':
      if (currentState == OFF) {
        currentState = ON;
        digitalWrite(ledPin, HIGH);
        Serial.println("เปิด LED");
      }
      break;
    case '0':
      if (currentState == ON) {
        currentState = OFF;
        digitalWrite(ledPin, LOW);
        Serial.println("ปิด LED");
      }
      break;
    default:
      Serial.println("คำสั่งไม่ถูกต้อง");
  }
}
*/