// 1.กดปุ่มที่1เพิ่มความเร็วมอเตอร์ และกดปุ่มที่2 ลดความเร็วมอเตอร์ 
// 1.กดปุ่มที่1เพิ่มความเร็วมอเตอร์ และกดปุ่มที่2 ลดความเร็วมอเตอร์ 
#include <Arduino.h>
const int SPEED_UP= 0;
const int SPEED_DOWN= 1;
const int SPEED = 2;
int state;

//const int buttonPin1 = 2;  // กำหนดขาที่เชื่อมกับปุ่ม 1
//const int buttonPin2 = 3;  // กำหนดขาที่เชื่อมกับปุ่ม 2

int motorSpeed = 50;  // ความเร็วเริ่มต้นของมอเตอร์

//enum State { IDLE, INCREASE_SPEED, DECREASE_SPEED };
//State currentState = IDLE;

void setup() {
  Serial.begin(115200);
  state = SPEED;
  
  pinMode(D5, INPUT);
  pinMode(D6, INPUT);
  pinMode(D0, OUTPUT);
  pinMode(D1, OUTPUT);
}
/*
void loop() {
  if(state == SPEED){
    analogWrite(D0, motorSpeed);
    analogWrite(D1, 0);
    if (digitalRead(D5)==HIGH){
      state = SPEED_UP;
    }
    else if (digitalRead(D6)==HIGH){
      state = SPEED_DOWN;
    }
  }
  else if (state == SPEED_UP){
    motorSpeed = motorSpeed + 10;
    Serial.println("เพิ่มความเร็ว: " + String(motorSpeed));
    state = SPEED;
  }
  else if (state == SPEED_DOWN){
    motorSpeed = motorSpeed - 10;
    Serial.println("ลดความเร็ว: " + String(motorSpeed));
   state = SPEED;
  }
\
}
*/
void loop() {
  switch (state) {
    
    case SPEED:
      Serial.println("ความเร็วปัจจุบัน: " + String(motorSpeed));
      if (digitalRead(D5) == 1) {
        state = SPEED_UP;
      //  Serial.println("ปุ่ม 1 ถูกกด");
      } else if (digitalRead(D6) == 1) {
        state = SPEED_DOWN;
      //  Serial.println("ปุ่ม 2 ถูกกด");
      }
      analogWrite(D0, motorSpeed);
      analogWrite(D1, 0);
      break; 

    case SPEED_UP:
      if (motorSpeed < 100) {
        //Serial.print("เพิ่มความเร็ว");
        motorSpeed = motorSpeed + 10;  // เพิ่มความเร็วทีละ 10
      
      }
      Serial.println("เพิ่มความเร็ว: " + String(motorSpeed));
      state = SPEED;
      delay(500);
      break;

    case SPEED_DOWN:
      if (motorSpeed > 0) {
        motorSpeed = motorSpeed-10;  // ลดความเร็วทีละ 10
      }
      Serial.println("ลดความเร็ว: " + String(motorSpeed));
      state = SPEED;
      delay(500);
      break;

  }
}
  
  // นำความเร็วไปควบคุมมอเตอร์ หรือทำงานอื่น ๆ ที่คุณต้องการที่นี่





/*
#include <Arduino.h>
const int TURN_RIGHT= 0;
const int TURN_LEFT = 1;
int state;
int motorSpeed = 50;
void setup()
{
    state = TURN_RIGHT;
    pinMode(D0, OUTPUT);
    pinMode(D1, OUTPUT);
}
void loop()
{
    if (state == TURN_RIGHT)
    {
        analogWrite(D0, motorSpeed);
        analogWrite(D1, 0);
        delay(1000);
        state = TURN_LEFT;
    }
    else if (state == TURN_LEFT)
    {
        analogWrite(D0, 0);
        analogWrite(D1, motorSpeed);
        delay(1000);
        state = TURN_RIGHT;
    }
}
*/