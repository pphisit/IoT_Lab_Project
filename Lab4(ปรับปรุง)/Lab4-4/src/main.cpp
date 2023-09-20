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
const float tempThreshold2 = 26.0;
const float tempThreshold3 = 27.0;

float currentTemperature;
float temperature;

// กำหนดตัวแปรสำหรับ State Machine
enum State { MEASURE_TEMPERATURE, CHECK_THRESHOLD, ALERT };
State currentState = MEASURE_TEMPERATURE;

void setup() {
  // เริ่มต้น Serial Monitor
  Serial.begin(115200);

  // กำหนดขาที่เชื่อมกับ LED เป็น OUTPUT
  pinMode(ledPin1, OUTPUT);
  pinMode(ledPin2, OUTPUT);
  pinMode(ledPin3, OUTPUT);

  // เริ่มต้นเซนเซอร์ SHTC3
  Wire.begin();
  lcd.init();
  lcd.backlight();
  // รอสักครู่ให้เซนเซอร์เตรียมตัว
  //delay(500);
}

void loop() {
  switch (currentState) {
    case MEASURE_TEMPERATURE:
      // อ่านค่าอุณหภูมิจากเซนเซอร์ SHTC3
      shtc3.begin();
      shtc3.sample();
      temperature = shtc3.readTempC();
      

      // แสดงค่าอุณหภูมิบนจอ LCD
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Temp: ");
      lcd.setCursor(6, 0);
      lcd.print(temperature, 1);
      lcd.setCursor(13, 0);
      lcd.print("C");
      Serial.print("Temperature: ");
      Serial.println(temperature);
        delay(1000);
      // เปลี่ยนสถานะเพื่อตรวจสอบค่าอุณหภูมิ
      currentState = CHECK_THRESHOLD;
      break;
    case CHECK_THRESHOLD:
      // อ่านค่าอุณหภูมิ
      currentTemperature = shtc3.readTempC();

      // ตรวจสอบและควบคุม LED ตามค่าอุณหภูมิ
      if (currentTemperature >= tempThreshold1) {
        digitalWrite(ledPin1, HIGH);
      } else {
        digitalWrite(ledPin1, LOW);
      }

      if (currentTemperature >= tempThreshold2) {
        digitalWrite(ledPin2, HIGH);
      } else {
        digitalWrite(ledPin2, LOW);
      }

      if (currentTemperature >= tempThreshold3) {
        digitalWrite(ledPin3, HIGH);
      } else {
        digitalWrite(ledPin3, LOW);
      }

      // กลับไปวัดอุณหภูมิอีกครั้ง
      currentState = MEASURE_TEMPERATURE;
      break;
  }
}
