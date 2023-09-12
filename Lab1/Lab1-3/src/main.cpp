#include <Arduino.h>

// กำหนดขา GPIO ที่เชื่อมกับ LED 7-Segment 4 หลัก
int Digit_pins[] = {D0,D1,D2,D3};
int Segment_pin[] = {D4, D5, D6, D7, D8, D9, D10}; //กำหนด Port สำหรับขา Segment  A ถึง G

const int SHOW_DIGIT_1 = 1;
const int SHOW_DIGIT_2 = 2;
const int SHOW_DIGIT_3 = 3;
const int SHOW_DIGIT_4 = 4;
int state ;
int number[10] = {0x3F, 0x06, 0x5B, 0x4F, 0x66,
                  0x6D, 0x7D, 0x07, 0x7F, 0x6F};

// แบบอักษร 7-Segment สำหรับแสดงตัวเลข 0-9
/*const byte digits[10] = {
  B11111100, // 0
  B01100000, // 1
  B11011010, // 2
  B11110010, // 3
  B01100110, // 4
  B10110110, // 5
  B10111110, // 6
  B11100000, // 7
  B11111110, // 8
  B11110110  // 9
};
*/

// กำหนดสถานะของ State Machine


void setup() {
  // เริ่มต้น Serial Monitor
  Serial.begin(115200);

  // กำหนดขาที่เชื่อมกับ LED 7-Segment เป็น OUTPUT
  for (int i = 0; i < 4; i++) {
    pinMode(Digit_pins[i], OUTPUT);
    digitalWrite(Segment_pin[i], LOW);
  }
}

void loop() {
  switch (state) {
    case SHOW_DIGIT_1:
      displayDigit(number[2]);
      state = SHOW_DIGIT_2;
      delay(1000);
      break;

    case SHOW_DIGIT_2:
      displayDigit(number[0]);
      state = SHOW_DIGIT_3;
      delay(1000);
      break;

    case SHOW_DIGIT_3:
      displayDigit(number[0]);
      state = SHOW_DIGIT_3;
      delay(1000);
      break;

    case SHOW_DIGIT_4:
      displayDigit(number[2]);
      state = SHOW_DIGIT_4;
      delay(1000);
      break;
  }
}

void displayDigit(int value) {
  for (int i = 0; i < 8; i++) {
    digitalWrite(Digit_pins[i], bitRead(value, i));
  }
}



/*
#include <ESP8266WiFi.h>

// กำหนดขา GPIO ที่เชื่อมกับ LED 7-Segment 4 หลัก
const int segmentPins[4] = {2, 3, 4, 5};

// แบบอักษร 7-Segment สำหรับแสดงตัวเลข 0-9
const byte digits[10] = {
  B11111100, // 0
  B01100000, // 1
  B11011010, // 2
  B11110010, // 3
  B01100110, // 4
  B10110110, // 5
  B10111110, // 6
  B11100000, // 7
  B11111110, // 8
  B11110110  // 9
};

// กำหนดสถานะของ State Machine
enum State { DISPLAY_DIGIT1, DISPLAY_DIGIT2, DISPLAY_DIGIT3, DISPLAY_DIGIT4 };
State currentState = DISPLAY_DIGIT1;

void setup() {
  // เริ่มต้น Serial Monitor
  Serial.begin(115200);

  // กำหนดขาที่เชื่อมกับ LED 7-Segment เป็น OUTPUT
  for (int i = 0; i < 4; i++) {
    pinMode(segmentPins[i], OUTPUT);
    digitalWrite(segmentPins[i], LOW);
  }
}

void loop() {
  switch (currentState) {
    case DISPLAY_DIGIT1:
      displayDigit(digits[0]);
      currentState = DISPLAY_DIGIT2;
      delay(1000);
      break;

    case DISPLAY_DIGIT2:
      displayDigit(digits[1]);
      currentState = DISPLAY_DIGIT3;
      delay(1000);
      break;

    case DISPLAY_DIGIT3:
      displayDigit(digits[2]);
      currentState = DISPLAY_DIGIT4;
      delay(1000);
      break;

    case DISPLAY_DIGIT4:
      displayDigit(digits[3]);
      currentState = DISPLAY_DIGIT1;
      delay(1000);
      break;
  }
}

void displayDigit(byte value) {
  for (int i = 0; i < 8; i++) {
    digitalWrite(segmentPins[i], bitRead(value, i));
  }
}
*/