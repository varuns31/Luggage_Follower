#include <SPI.h>
#include "DW1000Ranging.h"
 
#define SPI_SCK 14
#define SPI_MISO 13
#define SPI_MOSI 12
#define DW_CS 11
 
// connection pins
const uint8_t PIN_RST = 10; // reset pin
const uint8_t PIN_IRQ = 21; // irq pin
const uint8_t PIN_SS = 11;   // spi select pin
 
void setup()
{
    Serial.begin(115200);
    delay(1000);
    //init the configuration
    SPI.begin(SPI_SCK, SPI_MISO, SPI_MOSI);
    DW1000Ranging.initCommunication(PIN_RST, PIN_SS, PIN_IRQ); //Reset, CS, IRQ pin
    //define the sketch as anchor. It will be great to dynamically change the type of module
    DW1000Ranging.attachNewRange(newRange);
    DW1000Ranging.attachNewDevice(newDevice);
    DW1000Ranging.attachInactiveDevice(inactiveDevice);
    //Enable the filter to smooth the distance
    //DW1000Ranging.useRangeFilter(true);
 
    //we start the module as a tag
    DW1000Ranging.startAsTag("7D:00:22:EA:82:60:3B:9C", DW1000.MODE_LONGDATA_RANGE_LOWPOWER);
      Serial.print("Started: ");
}
 
void loop()
{
    float sum = 0;
    int num = 0;
    for(int i=0;i<10;)
    {
      float dist = DW1000Ranging.loop();
      if(dist > 0 && dist < 20)
      {
        sum = sum + dist;
        num++;
        i++;
      }
    }
    if(num > 0)
    {
      Serial.print("Data: ");
      Serial.println((float)sum/num);
    }
}
 
float newRange()
{
    // Serial.print("from: ");
    // Serial.print(DW1000Ranging.getDistantDevice()->getShortAddress(), HEX);
    // Serial.print("\t Range: ");
    float ret_val = DW1000Ranging.getDistantDevice()->getRange();
    // Serial.print(ret_val);
    // Serial.print(" m");
    // Serial.print("\t RX power: ");
    // Serial.print(DW1000Ranging.getDistantDevice()->getRXPower());
    // Serial.println(" dBm");
    return ret_val;
}
 
void newDevice(DW1000Device *device)
{
    Serial.print("ranging init; 1 device added ! -> ");
    Serial.print(" short:");
    Serial.println(device->getShortAddress(), HEX);
}
 
void inactiveDevice(DW1000Device *device)
{
    Serial.print("delete inactive device: ");
    Serial.println(device->getShortAddress(), HEX);
}