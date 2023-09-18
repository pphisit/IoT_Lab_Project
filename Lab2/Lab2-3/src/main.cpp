//3.LED 2 ดวงติดดับสลับกันโดยให้ ปุ่มกด 2 ปุ่ม เพิ่มและลดความเร็วการกระพริบ โดยกด 1 ครั้งจะเพิ่มและลดความเร็ว 
//ทีล่ะ 100 มิลลิวินาที ถ้าลดมากเกิน 1000 มิลลิวินาที ให้กลับมาเริ่มต้นที่ 100 มิลลิวินาที และถ้าเพิ่มต่ำกว่า 100 มิลลิวินาที 
//ให้กลับมาเริ่มต้นที่ 1000 มิลลิวินาที
#include <Arduino.h>

const int ledPin1 = D1;  // ขา LED 1
const int ledPin2 = D2;  // ขา LED 2
const int button1Pin = D7;  // ขาปุ่ม 1
const int button2Pin = D8;  // ขาปุ่ม 2
int delay1 = 100;
int press = 0;

enum State { LED_ON, SPEED_UP,SPEED_DOWN };
State currentState = SPEED_UP;

IRAM_ATTR void ButtonPress1() {
  currentState = SPEED_UP;
  Serial.print("Button1 up");
}

IRAM_ATTR void ButtonPress2() {
 currentState = SPEED_DOWN;
 Serial.print("Button2 down");
}
void setup() {
  Serial.begin(115200);
  pinMode(ledPin1, OUTPUT);
  pinMode(ledPin2, OUTPUT);
  pinMode(button1Pin, INPUT);
  pinMode(button2Pin, INPUT);
  attachInterrupt(digitalPinToInterrupt(button1Pin), ButtonPress1, RISING);
  attachInterrupt(digitalPinToInterrupt(button2Pin), ButtonPress2, RISING);

}
void loop() {
  switch (currentState) {
    case LED_ON:
      digitalWrite(ledPin1, HIGH);      
      digitalWrite(ledPin2, LOW);
      delay(delay1);
      digitalWrite(ledPin1, LOW);      
      digitalWrite(ledPin2, HIGH);
      delay(delay1);  
      Serial.println(delay1);             
      break;

    case SPEED_UP: 
         if (delay1 < 1000) {
        delay1 = delay1 + 100;  
      }
      else if (delay1 >= 1000){
        delay1 = 100; 
      } 
      Serial.print("Button1 up");
      Serial.println(delay1);
      currentState = LED_ON;    
      break;

    case SPEED_DOWN:
      if (delay1 > 100) {
        delay1 = delay1 - 100;  
      }
      else if (delay1 <= 100){
        delay1 = 100; 
      } 
      Serial.print("Button2 down");
      Serial.println(delay1);
      currentState = LED_ON;
      break;    
  }
}
