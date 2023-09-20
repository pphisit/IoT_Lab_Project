//1.กำหนดค่าเริ่มต้นของ RFID หลังจากนั้นให้มีการตรวจสอบค่าที่อ่านได้ ถ้าค่า RFID ตรงกับค่าที่เรากำหนด
//ให้แสดงผ่าน Serial Monitor “Correct RFID” ถ้าไม่ตรงให้แสดง “Incorrect RFID”

#include <Arduino.h>
#include <SPI.h>
#include <Wire.h>
#include <MFRC522.h>

#define RST_PIN D1
#define SS_PIN D2

// กำหนดค่าสถานะ
const int READ_RFID = 0;
const int CHECK_RFID = 1;
MFRC522 mfrc522(SS_PIN, RST_PIN);

// กำหนดตัวแปรสถานะเริ่มต้น
int state;
String initRFID = "54EA7AC";
String valRFID;
String readRFID();

void setup() {
  state = READ_RFID;
  Serial.begin(115200);
  SPI.begin();
  mfrc522.PCD_Init();
}

void loop() {
  // ตรวจสอบสถานะปัจจุบันและดำเนินการตาม
  switch (state) 
  {
    case READ_RFID: //อ่านค่า RFID
       if(mfrc522.PICC_IsNewCardPresent()&&mfrc522.PICC_ReadCardSerial())
       {
          valRFID = readRFID();
          Serial.println("==========");
          Serial.println("Read RFID");
          Serial.println("HEX: "+valRFID);
          Serial.println("==========");
          delay(1000);
          state = CHECK_RFID;
        }
        else{
        Serial.println("Wait RFID");
        delay(1000);
        }
        break;
       
    case CHECK_RFID:  //ตรวจสอบค่า RFID
        if (valRFID == initRFID) {
          Serial.println("Correct RFID");
          delay(500);

        } else {
          Serial.println("Incorrect RFID");
          delay(500);
        }
    state = READ_RFID;
    break;      
  }
}

String readRFID()
{
  String content;
    for(byte i =0; i<mfrc522.uid.size; i++)
     {
       content.concat(String(mfrc522.uid.uidByte[i] <0x10?"0":""));
       content.concat(String(mfrc522.uid.uidByte[i], HEX));
     }
  content.toUpperCase();
  return content.substring(1);
}