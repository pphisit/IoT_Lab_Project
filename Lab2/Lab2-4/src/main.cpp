//กำหนดใช้ LED 4 ดวง มีปุ่มกด 2 ปุ่ม โดยปุ่มที่ 1 สามารถควบคุม LED ขยับไปทางขวา ส่วนปุ่มที่ 2 สามารถควบคุมขยับไปทางซ้าย เมื่อกด 1 ครั้ง โดย LED เริ่มต้นจะอยู่ซ้ายมือสุด
//ใช้ Debounce 
#include <Arduino.h>
const int LED1 = 0;
const int LED2 = 1;
const int LED3 = 2;
const int LED4 = 3;
int state;
void setup()
{
  Serial.begin(115200);
  pinMode(D1, INPUT);
  pinMode(D2, INPUT);
  pinMode(D3, OUTPUT);
  pinMode(D4, OUTPUT);
  pinMode(D5, OUTPUT);
  pinMode(D6, OUTPUT);
  state = LED1;
}

void loop(){
  switch (state)
    {
    case LED1:        
        digitalWrite(D3, HIGH);
        digitalWrite(D4, LOW);
        digitalWrite(D5, LOW);
        digitalWrite(D6, LOW);
        if (digitalRead(D1) == HIGH){
            while (digitalRead(D1) == HIGH);       
            state = LED2; 
        }
        else if (digitalRead(D2) == HIGH)        
        {
          while (digitalRead(D2) == HIGH);
          state = LED4;
        }   
        break;
      case LED2:
        digitalWrite(D3, LOW);
        digitalWrite(D4, HIGH);
        digitalWrite(D5, LOW);
        digitalWrite(D6, LOW);
        if (digitalRead(D1) == HIGH)
        {
          while (digitalRead(D1) == HIGH);
          state = LED3; 
        }
        else if (digitalRead(D2) == HIGH)
        {
          while (digitalRead(D2) == HIGH);  
          state = LED1;
        }   
        break;
      case LED3:
        digitalWrite(D3, LOW);
        digitalWrite(D4, LOW);
        digitalWrite(D5, HIGH);
        digitalWrite(D6, LOW);
        if (digitalRead(D1) == HIGH)
        {
          while (digitalRead(D1) == HIGH);
          state = LED4; 
        }
        else if (digitalRead(D2) == HIGH)
        {
          while (digitalRead(D2) == HIGH);
          state = LED2;
        }   
        break;
      case LED4:
        digitalWrite(D3, LOW);
        digitalWrite(D4, LOW);
        digitalWrite(D5, LOW);
        digitalWrite(D6, HIGH);
        if (digitalRead(D1) == HIGH)
        {
          while (digitalRead(D1) == HIGH);
          state = LED1; 
        }
        else if (digitalRead(D2) == HIGH)
        {
          while (digitalRead(D2) == HIGH);
          state = LED3;
        }   
        break;
}
}
