//4.แจ้งเตือนผ่าน LED 3 ดวง เมื่อถึงค่าอุณหภูมิที่กำหนด
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
