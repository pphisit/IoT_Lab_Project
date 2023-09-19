//•	โจทย์ประยุกต์ แจ้งเตือนอุณหภูมิผ่าน LED 3 ดวง เมื่อถึงค่าอุณหภูมิที่กำหนด
#include <arduino.h>
#include <Wire.h>                  
#include "SHTC3.h"
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 16, 2); 
SHTC3 shtc3(Wire); 
// กำหนดขา GPIO ที่เชื่อมกับ LED
const int ledPin1 = D3;
const int ledPin2 = D4;
const int ledPin3 = D5;

// กำหนดค่าอุณหภูมิที่ต้องการสำหรับการเปิด LED
const float tempThreshold1 = 25.0;
const float tempThreshold2 = 27.0;
const float tempThreshold3 = 30.0;

// กำหนดตัวแปรสำหรับ State Machine
enum State { MEASURE_TEMPERATURE, CHECK_THRESHOLD };
State currentState = MEASURE_TEMPERATURE;

// สร้างอินสแตนซ์ของ SHTC3


void setup() {
  // เริ่มต้น Serial Monitor
  Serial.begin(115200);

  // กำหนดขาที่เชื่อมกับ LED เป็น OUTPUT
  pinMode(ledPin1, OUTPUT);
  pinMode(ledPin2, OUTPUT);
  pinMode(ledPin3, OUTPUT);
  
  // กำหนดขนาดของจอ LCD (จอ 16x2)
  lcd.begin(16, 2);

  // เริ่มต้นเซนเซอร์ SHTC3
  Wire.begin();
  lcd.begin();
  lcd.backlight();
  // รอสักครู่ให้เซนเซอร์เตรียมตัว
  //delay(500);
}

void loop() {
  switch (currentState) {
    case MEASURE_TEMPERATURE:
      // อ่านค่าอุณหภูมิจากเซนเซอร์ SHTC3
      float temperature = shtc3.readTemperature();

      // แสดงค่าอุณหภูมิบนจอ LCD
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Temp: ");
      lcd.setCursor(7, 1);
      lcd.print(temperature, 1);
      lcd.setCursor(9, 1);
      lcd.print("C");

      // เปลี่ยนสถานะเพื่อตรวจสอบค่าอุณหภูมิ
      currentState = CHECK_THRESHOLD;
      break;

    case CHECK_THRESHOLD:
      // อ่านค่าอุณหภูมิ
      float currentTemperature = shtc3.readTemperature();

      // ตรวจสอบและควบคุม LED ตามค่าอุณหภูมิ
      if (currentTemperature >= tempThreshold1) {
        digitalWrite(ledPin1, HIGH);
      } else {
        digitalWrite(ledPin1, LOW);
        digitalWrite(ledPin1, LOW); 
        digitalWrite(ledPin1, LOW);         
      }

      if (currentTemperature >= tempThreshold2) {
        digitalWrite(ledPin1, HIGH);
        digitalWrite(ledPin2, HIGH);
      } else {
        digitalWrite(ledPin1, LOW);
        digitalWrite(ledPin2, LOW); 
        digitalWrite(ledPin3, LOW); 
      }

      if (currentTemperature >= tempThreshold3) {
        digitalWrite(ledPin1, HIGH);
        digitalWrite(ledPin2, HIGH);
        digitalWrite(ledPin3, HIGH);
      } else {
        digitalWrite(ledPin1, LOW);
        digitalWrite(ledPin2, LOW); 
        digitalWrite(ledPin3, LOW); 
      }
      // กลับไปวัดอุณหภูมิอีกครั้ง
      currentState = MEASURE_TEMPERATURE;
      break;
  }
}

/*
//4.กำหนดใช้ LED 4 ดวง มีปุ่มกด 2 ปุ่ม โดยปุ่มที่ 1 สามารถควบคุม LED ขยับไปทางขวา ส่วนปุ่มที่ 2 สามารถควบคุมขยับไปทางซ้าย เมื่อกด 1 ครั้ง โดย LED เริ่มต้นจะอยู่ซ้ายมือสุด     
#include <Arduino.h>

// กำหนดขาของ LED
const int ledPins[] = {D1, D2};
//const int numLEDs = sizeof(ledPins) / sizeof(ledPins[0]);

// กำหนดขาของปุ่ม
const int buttonChangeStatePin = D7;
const int buttonReduceLEDPin = D8;

// กำหนดสถานะ
enum State {
  STATE_1,
  STATE_2,
  STATE_3,
  STATE_4
};



State currentState = STATE_1;
//int numActiveLEDs = 1;
/*
void changeState() {
  // เปลี่ยนสถานะแต่ละครั้งที่ปุ่มถูกกด
  switch (currentState) {
    case STATE_1:
      digitalWrite(ledPins[0], HIGH);
      digitalWrite(ledPins[1], LOW);      
      currentState = STATE_2;      
      break;
    case STATE_2:
      digitalWrite(ledPins[0], LOW);
      digitalWrite(ledPins[1], HIGH);
      currentState = STATE_3;
      break;
    case STATE_3:
      currentState = STATE_4;
      break;
    case STATE_4:
      currentState = STATE_1;
      break;
  }
}

void reduceLEDCount() {
  // ลดจำนวน LED ที่ติดตาม State Machine
  if (numActiveLEDs > 1) {
    numActiveLEDs--;
  }
}

void updateLEDs() {
  // ปิด LED ทุกดวง
  for (int i = 0; i < numLEDs; i++) {
    digitalWrite(ledPins[i], LOW);
  }

  // เปิด LED ตามจำนวนที่ต้องการ
  for (int i = 0; i < numActiveLEDs; i++) {
    digitalWrite(ledPins[i], HIGH);
  }
}
*/
/*
void setup() {
  // กำหนดขา LED เป็น OUTPUT
 // for (int i = 0; i < numLEDs; i++) {
 //   pinMode(ledPins[i], OUTPUT);
 //   digitalWrite(ledPins[i], LOW);  // ปิด LED ทุกดวงเริ่มต้น
 // }
  pinMode(D1, OUTPUT);
  pinMode(D2, OUTPUT);
  // กำหนดขาปุ่มเป็น INPUT_PULLUP
  pinMode(buttonChangeStatePin, INPUT);
  pinMode(buttonReduceLEDPin, INPUT);

  Serial.begin(115200);
}

void loop() {
  // อ่านสถานะปุ่มเพื่อเปลี่ยนสถานะ
  if (digitalRead(buttonChangeStatePin) == LOW) {
    Serial.println("buttonChangeStatePin");
    currentState = static_cast<State>((currentState + 1));
    //changeState();
    delay(100);  // ป้องกันการกระโดดสถานะ
  }

  // อ่านสถานะปุ่มเพื่อลดจำนวน LED
  if (digitalRead(buttonReduceLEDPin) == HIGH) {
    currentState = static_cast<State>((currentState - 1));
   // reduceLEDCount();
    delay(100);  // ป้องกันการกระโดดสถานะ
  }

 switch (currentState) {
    case STATE_1:
      digitalWrite(ledPins[0], HIGH);
      digitalWrite(ledPins[1], LOW);   
      Serial.println("STATE_1");   
      currentState = STATE_2;      
      break;
    case STATE_2:
      digitalWrite(ledPins[0], LOW);
      digitalWrite(ledPins[1], HIGH);
      Serial.println("STATE_2");
      currentState = STATE_3;
      break;
    case STATE_3:
      currentState = STATE_4;
      break;
    case STATE_4:
      currentState = STATE_1;
      break;
  }
}
  // อัพเดทสถานะ LED ตาม State Machine

*/