// 3.แสดงตัวเลข 1234 ผ่าน 7-segment ด้วย MCP23008

#include <Arduino.h>
#include <Adafruit_MCP23X08.h> // ประกาศใช้งานไลบารี่ Adafruit_MCP23X08
Adafruit_MCP23X08 mcp;         // ประกาศตัวแปร mcp ให้เป็นตัวแปรของคลาส Adafruit_MCP23X08
int Digit_pins[] = {D0, D1, D2, D3};               // กำหนด Port สำหรับขา Digit 4 ถึง 1
int Segment_pin[] = {D4, D5, D6, D7, D8, D9, D10}; // กำหนด Port สำหรับขา Segment  A ถึง G
const int SHOW_DIGIT_1 = 1;
const int SHOW_DIGIT_2 = 2;
const int SHOW_DIGIT_3 = 3;
const int SHOW_DIGIT_4 = 4;

int state;
void setup()
{
    state = SHOW_DIGIT_1;
    // กำหนดให้ขาที่ใช้เป็น Output ประกาศทีล่ะ Port จากตัวแปร Digit_pins
    for (int i = 0; i < 4; i++)
    {
        pinMode(Digit_pins[i], OUTPUT);
    }
    // กำหนดให้ขาที่ใช้เป็น Output ประกาศทีล่ะ Port จากตัวแปร Segment_pin
    for (int i = 0; i < 7; i++)
    {
        pinMode(Segment_pin[i], OUTPUT);
    }
    mcp.begin_I2C();        // กำหนดใช้งานโปรโตคอล I2C
    mcp.pinMode(0, OUTPUT); // กำหนดขา 0 ให้เป็น OUTPUT

}
void loop()
{
                  if (state == SHOW_DIGIT_1)
    {
         // กำหนดให้ขาเปิดใช้ขา Digit 1 ทำงาน และปิดขา Digit 2,3,4
        digitalWrite(Digit_pins[0], HIGH);
        digitalWrite(Digit_pins[1], HIGH);
        digitalWrite(Digit_pins[2], HIGH);
        digitalWrite(Digit_pins[3], LOW);
        // แสดงเลข 4 บน 7 Segment
        digitalWrite(Segment_pin[0], LOW);
        digitalWrite(Segment_pin[1], HIGH);
        digitalWrite(Segment_pin[2], HIGH);
        digitalWrite(Segment_pin[3], LOW);
        digitalWrite(Segment_pin[4], LOW);
        digitalWrite(Segment_pin[5], HIGH);
        digitalWrite(Segment_pin[6], HIGH);
        delay(1);
        state = SHOW_DIGIT_2;
    }
    else if (state == SHOW_DIGIT_2)
    {
        // กำหนดให้ขาเปิดใช้ขา Digit 2 ทำงาน และปิดขา Digit 1,3,4
        digitalWrite(Digit_pins[0], HIGH);
        digitalWrite(Digit_pins[1], HIGH);
        digitalWrite(Digit_pins[2], LOW);
        digitalWrite(Digit_pins[3], HIGH);
        // แสดงเลข 3 บน 7 Segment
        digitalWrite(Segment_pin[0], HIGH);
        digitalWrite(Segment_pin[1], HIGH);
        digitalWrite(Segment_pin[2], HIGH);
        digitalWrite(Segment_pin[3], HIGH);
        digitalWrite(Segment_pin[4], LOW);
        digitalWrite(Segment_pin[5], LOW);
        digitalWrite(Segment_pin[6], HIGH);
        delay(1);
        state = SHOW_DIGIT_3;
    }
    else if (state == SHOW_DIGIT_3)
    {
        // กำหนดให้ขาเปิดใช้ขา Digit 3 ทำงาน และปิดขา Digit 1,2,4
        digitalWrite(Digit_pins[0], HIGH);
        digitalWrite(Digit_pins[1], LOW);
        digitalWrite(Digit_pins[2], HIGH);
        digitalWrite(Digit_pins[3], HIGH);
        // แสดงเลข 2 บน 7 Segment
        digitalWrite(Segment_pin[0], HIGH);
        digitalWrite(Segment_pin[1], HIGH);
        digitalWrite(Segment_pin[2], LOW);
        digitalWrite(Segment_pin[3], HIGH);
        digitalWrite(Segment_pin[4], HIGH);
        digitalWrite(Segment_pin[5], LOW);
        digitalWrite(Segment_pin[6], HIGH);
        delay(1);
        state = SHOW_DIGIT_4;
    }
    else if (state == SHOW_DIGIT_4)
    {
         // กำหนดให้ขาเปิดใช้ขา Digit 4 ทำงาน และปิดขา Digit 1,2,3
        digitalWrite(Digit_pins[0], LOW);
        digitalWrite(Digit_pins[1], HIGH);
        digitalWrite(Digit_pins[2], HIGH);
        digitalWrite(Digit_pins[3], HIGH);
        // แสดงเลข 1 บน 7 Segment
        digitalWrite(Segment_pin[0], LOW);
        digitalWrite(Segment_pin[1], HIGH);
        digitalWrite(Segment_pin[2], HIGH);
        digitalWrite(Segment_pin[3], LOW);
        digitalWrite(Segment_pin[4], LOW);
        digitalWrite(Segment_pin[5], LOW);
        digitalWrite(Segment_pin[6], LOW);
        delay(1);
        state = SHOW_DIGIT_1;
    }
}
