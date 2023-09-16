// Example By ArduinoAll.com
// www.ArduinoAll.com

#include <Arduino.h>
#include "SHTC3.h"

SHTC3 s(Wire);

void setup() {
  Serial.begin(9600);
  Wire.begin();
}

void loop() {
  s.begin(true);
  s.sample();
  Serial.print(F("[SHTC3] T:"));
  Serial.print(s.readTempC());
  Serial.print(F(" C?  /   H: "));
  Serial.print(s.readHumidity());
  Serial.println(F(" %"));
  delay(2000);
}