//1. แสดงค่าตัวต้านทานปรับค่าได้ผ่าน LCD โดยให้ข้อความอยู่ตรงกลาง กำหนดช่วงตัวต้านทาน 0-100
#include "Arduino.h"
#include "Wire.h"                   // เรียกใช้งาน Library Wire
#include "LiquidCrystal_I2C.h"      // เรียกใช้งาน Library LiquidCrystal_I2C
LiquidCrystal_I2C lcd(0x27, 16, 2); // ประกาศ Address กำหนดขนาดของหน้าจอ
const int DISPLAY = 0;
int state;
int val;
void setup()
{
  state = DISPLAY;
  lcd.init();      // เรียกใช้งาน lcd
  lcd.backlight(); // เปิดใช้งาน Backlight
  pinMode(A0, INPUT);
}
void loop()
{
  val=map(analogRead(A0),0,1023,0,100);
  switch (state)
  {
  case DISPLAY:
    lcd.setCursor(5, 0);      // กำหนดตำแหน่งตำแหน่งที่ 0 แถวที่ 0
    lcd.print("ค่าความต้านทาน"); // กำหนดข้อความที่จะแสดง
    lcd.setCursor(8, 1);      // กำหนดตำแหน่งตำแหน่งที่ 0 แถวที่ 1
    lcd.print(val); // กำหนดข้อความที่จะแสดง
    break;
  }
}