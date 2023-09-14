//4.ใช้ตัวต้านทานปรับค่าได้ เพิ่มลดความเร็วมอเตอร์และใช้ปุ่ม เพื่อเปลี่ยนการหมุนมอเตอร์เป็นทวนเข็มนาฬิกาและตามเข็มนาฬิกาผ่าน
//อยากทดสอบใหม่

#include <Arduino.h>

const int buttonPin = D1;
const int motorPin1 = D5; 
const int motorPin2 = D6; 
int motorSpeed ;
int state;
const int CLOCKWISE = 0;
const int ANTICLOCKWISE = 1;

void setup() {
  Serial.begin(115200); 
  pinMode(motorPin1, OUTPUT);
  pinMode(motorPin2, OUTPUT);
  pinMode(buttonPin, INPUT);
  state = CLOCKWISE;
}

void loop() {

  switch (state) {

    case CLOCKWISE:
      motorSpeed =map(analogRead(A0),0,1023,0,255);
      Serial.println("clockwise  "+ String(motorSpeed));
      analogWrite(motorPin1, motorSpeed); 
      analogWrite(motorPin2, LOW);
      if (digitalRead(buttonPin) == HIGH){
        state = ANTICLOCKWISE; 
      } 
      break;

    case ANTICLOCKWISE:     
      motorSpeed =map(analogRead(A0),0,1023,0,255);
      Serial.println("anticlockwise  "+ String(motorSpeed));
      analogWrite(motorPin1, LOW); 
      analogWrite(motorPin2, motorSpeed);
      if (digitalRead(buttonPin) == HIGH){
        state = CLOCKWISE; 
      } 
      break;
      }      
  }

