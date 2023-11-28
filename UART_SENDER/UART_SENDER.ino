// #include <HardwareSerial.h>

// HardwareSerial SerialPort(2); // use UART2


void setup()  
{
  Serial.begin(19200); 
} 
void loop()  
{ 
  Serial.print(1);
  delay(1000);
  Serial.print(0);
  delay(1000);
}