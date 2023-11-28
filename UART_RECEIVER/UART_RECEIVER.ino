#include <HardwareSerial.h>

HardwareSerial SerialPort(1); // use UART2


char number  = ' ';
int LED = 15;

void setup()
{
  SerialPort.begin(19200, SERIAL_8N1, 13,12);
  Serial.begin(115200);
  pinMode(LED, OUTPUT);
  Serial.print("Started");
}
void loop()
{
  if (SerialPort.available())
  {
    char number = SerialPort.read();
    if (number == '0') {
      Serial.println(number);
    }
    if (number == '1') {
       Serial.println(number);
    }
  }
}