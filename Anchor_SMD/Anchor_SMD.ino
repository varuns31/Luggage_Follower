// #include <SPI.h>
// #include "DW1000Ranging.h"
// #include "DW1000.h"
 
// // leftmost two bytes below will become the "short address"
// char anchor_addr[] = "84:00:5B:D5:A9:9A:E2:9C"; //#4
 
// //calibrated Antenna Delay setting for this anchor
// uint16_t Adelay = 16533;
 
// // previously determined calibration results for antenna delay
// // #1 16630
// // #2 16610
// // #3 16607
// // #4 16580
 
// // calibration distance
// float dist_m = 0.6; //meters
 
// #define SPI2_SCK 36
// #define SPI2_MISO 35
// #define SPI2_MOSI 48
// #define DW2_CS 47
 
// // connection pins

// const uint8_t PIN2_RST = 16; // reset pin
// const uint8_t PIN2_IRQ = 15; // irq pin
// const uint8_t PIN2_SS = 47;   // spi select pin
 
// void setup()
// {
//   Serial.begin(115200);
//   delay(1000); //wait for serial monitor to connect
//   Serial.println("Anchor config and start");
//   Serial.print("Antenna delay ");
//   Serial.println(Adelay);
//   Serial.print("Calibration distance ");
//   Serial.println(dist_m);
 
//   //init the configuration
//   SPI.begin(SPI2_SCK, SPI2_MISO, SPI2_MOSI);
//   DW1000Ranging.initCommunication(PIN2_RST, PIN2_SS, PIN2_IRQ); //Reset, CS, IRQ pin
 
//   // set antenna delay for anchors only. Tag is default (16384)
//   DW1000.setAntennaDelay(Adelay);
 
//   DW1000Ranging.attachNewRange(newRange);
//   DW1000Ranging.attachNewDevice(newDevice);
//   DW1000Ranging.attachInactiveDevice(inactiveDevice);
 
//   //start the module as an anchor, do not assign random short address
//   DW1000Ranging.startAsAnchor(anchor_addr, DW1000.MODE_LONGDATA_RANGE_LOWPOWER, false);
//   // DW1000Ranging.startAsAnchor(ANCHOR_ADD, DW1000.MODE_SHORTDATA_FAST_LOWPOWER);
//   // DW1000Ranging.startAsAnchor(ANCHOR_ADD, DW1000.MODE_LONGDATA_FAST_LOWPOWER);
//   // DW1000Ranging.startAsAnchor(ANCHOR_ADD, DW1000.MODE_SHORTDATA_FAST_ACCURACY);
//   // DW1000Ranging.startAsAnchor(ANCHOR_ADD, DW1000.MODE_LONGDATA_FAST_ACCURACY);
//   // DW1000Ranging.startAsAnchor(ANCHOR_ADD, DW1000.MODE_LONGDATA_RANGE_ACCURACY);
// }
 
// void loop()
// {
//   DW1000Ranging.loop();
// }
 
// void newRange()
// {
//   //    Serial.print("from: ");
//   Serial.print(DW1000Ranging.getDistantDevice()->getShortAddress(), HEX);
//   Serial.print(", ");
 
// #define NUMBER_OF_DISTANCES 1
//   float dist = 0.0;
//   for (int i = 0; i < NUMBER_OF_DISTANCES; i++) {
//     dist += DW1000Ranging.getDistantDevice()->getRange();
//   }
//   dist = dist/NUMBER_OF_DISTANCES;
//   Serial.println(dist);
// }
 
// void newDevice(DW1000Device *device)
// {
//   Serial.print("Device added: ");
//   Serial.println(device->getShortAddress(), HEX);
// }
 
// void inactiveDevice(DW1000Device *device)
// {
//   Serial.print("Delete inactive device: ");
//   Serial.println(device->getShortAddress(), HEX);
// }
#include <SPI.h>
#include <HardwareSerial.h>
#include "DW1000Ranging.h"     //https://github.com/thotro/arduino-dw1000
 
#define ANCHOR_ADD "83:17:5B:D5:A9:9A:E2:9C"
HardwareSerial SerialPort(1); // use UART2
 
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
    // SerialPort.begin(19200, SERIAL_8N1,13,12);
    delay(1000);
    //init the configuration
    SPI.begin(SPI_SCK, SPI_MISO, SPI_MOSI);
    DW1000Ranging.initCommunication(PIN_RST, PIN_SS, PIN_IRQ); //Reset, CS, IRQ pin
    //define the sketch as anchor. It will be great to dynamically change the type of module
    DW1000Ranging.attachNewRange(newRange);
    DW1000Ranging.attachBlinkDevice(newBlink);
    DW1000Ranging.attachInactiveDevice(inactiveDevice);
    //Enable the filter to smooth the distance
    //DW1000Ranging.useRangeFilter(true);
 
    //we start the module as an anchor
    // DW1000Ranging.startAsAnchor("82:17:5B:D5:A9:9A:E2:9C", DW1000.MODE_LONGDATA_RANGE_ACCURACY);
 
    DW1000Ranging.startAsAnchor(ANCHOR_ADD, DW1000.MODE_LONGDATA_RANGE_LOWPOWER, false);
    Serial.print("Started");
    // DW1000Ranging.startAsAnchor(ANCHOR_ADD, DW1000.MODE_SHORTDATA_FAST_LOWPOWER);
    // DW1000Ranging.startAsAnchor(ANCHOR_ADD, DW1000.MODE_LONGDATA_FAST_LOWPOWER);
    // DW1000Ranging.startAsAnchor(ANCHOR_ADD, DW1000.MODE_SHORTDATA_FAST_ACCURACY);
    // DW1000Ranging.startAsAnchor(ANCHOR_ADD, DW1000.MODE_LONGDATA_FAST_ACCURACY);
    // DW1000Ranging.startAsAnchor(ANCHOR_ADD, DW1000.MODE_LONGDATA_RANGE_ACCURACY);
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
      Serial.print("Data from main anchor: ");
      Serial.println((float)sum/num);
    }
    // if (SerialPort.available())
    // {
    //   float number = SerialPort.read();
    //   Serial.print("Data from secondary anchor: ");
    //   Serial.println(number);
    // }
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
 
void newBlink(DW1000Device *device)
{
    Serial.print("blink; 1 device added ! -> ");
    Serial.print(" short:");
    Serial.println(device->getShortAddress(), HEX);
}
 
void inactiveDevice(DW1000Device *device)
{
    Serial.print("delete inactive device: ");
    Serial.println(device->getShortAddress(), HEX);
}