//2. ต่อวงจร LED ไฟวิ่งจำนวน 5 ดวง ด้วย MCP23008

#include <Arduino.h>
#include <Adafruit_MCP23x08.h>
Adafruit_MCP23X08 mcp;
int state;
const int LED1 = 1;
const int LED2 = 2;
const int LED3 = 3;
const int LED4 = 4;
const int LED5 = 5;
void setup()
{
  state = LED1;
  mcp.begin_I2C();
  for (int i = 1; i < 5; i++)
  {
    mcp.pinMode(i, OUTPUT);
  }
}
void loop()
{
  switch (state)
  {
  case LED1:
    digitalWrite(5, LOW);
    digitalWrite(1, HIGH);
        delay(1000);

    state = LED2;

    break;

  case LED2:
    digitalWrite(1, LOW);
    digitalWrite(2, HIGH);
        delay(1000);

    state = LED3;

    break;

  case LED3:
    digitalWrite(2, LOW);
    digitalWrite(3, HIGH);
        delay(1000);

    state = LED4;

    break;

  case LED4:
    digitalWrite(3, LOW);
    digitalWrite(4, HIGH);
        delay(1000);

    state = LED5;
    break;

  case LED5:
    digitalWrite(4, LOW);
    digitalWrite(5, HIGH);
    delay(1000);
    state = LED1;
    break;
  }
}