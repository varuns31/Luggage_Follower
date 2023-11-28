#include <SPI.h>
#include "DW1000Ranging.h"

// For the first anchor
#define SPI_SCK 18
#define SPI_MISO 19
#define SPI_MOSI 23
#define DW_CS 4
const uint8_t PIN_RST = 27;
const uint8_t PIN_IRQ = 34;
const uint8_t PIN_SS = 4;

// For the second anchor
#define SPI_SCK2 33  // Change this to the actual pin
#define SPI_MISO2 12 // Change this to the actual pin
#define SPI_MOSI2 13 // Change this to the actual pin
#define DW_CS2 15    // Change this to the actual pin
const uint8_t PIN_RST2 = 22; // Change this to the actual pin
const uint8_t PIN_IRQ2 = 2;  // Change this to the actual pin
const uint8_t PIN_SS2 = 15;  // Change this to the actual pin

SPIClass spi,spi2;

void setup()
{
    Serial.begin(115200);
    delay(1000);

    // Initialize the configuration for the first anchor

    spi.begin(SPI_SCK, SPI_MISO, SPI_MOSI, PIN_SS);
    DW1000Ranging.initCommunication(PIN_RST, PIN_SS, PIN_IRQ ,spi , 1);
   
    // Initialize the configuration for the second anchor
    spi2.begin(SPI_SCK2, SPI_MISO2, SPI_MOSI2, PIN_SS2);
    DW2_1000Ranging.initCommunication(PIN_RST2, PIN_SS2, PIN_IRQ2 , 
    spi2 , 2);
   
   
    DW1000Ranging.attachNewRange(newRange);
    DW1000Ranging.attachNewDevice(newDevice);
    DW1000Ranging.attachInactiveDevice(inactiveDevice);
    DW1000Ranging.startAsAnchor("82:17:5B:D5:A9:9A:E2:9C", DW1000.MODE_LONGDATA_RANGE_LOWPOWER, false);

    // Wait for some time before initializing the second anchor
    delay(5000);
    // pinMode(PIN_SS, OUTPUT);
    // digitalWrite(PIN_SS, HIGH);
    // pinMode(PIN_SS2, OUTPUT);
    // digitalWrite(PIN_SS2, LOW);

    DW2_1000Ranging.attachNewRange(newRange2);
    DW2_1000Ranging.attachNewDevice(newDevice2);
    DW2_1000Ranging.attachInactiveDevice(inactiveDevice2);
    DW2_1000Ranging.startAsAnchor("20:00:00:00:00:9A:E2:9D", DW1000.MODE_LONGDATA_RANGE_LOWPOWER, false);
}

void loop()
{
    // digitalWrite(PIN_SS, LOW);
    DW1000Ranging.loop();
    // digitalWrite(PIN_SS, HIGH);
    // digitalWrite(PIN_SS2, LOW);
    // DW2_1000Ranging.loop();
    // digitalWrite(PIN_SS2, HIGH);
}

void newRange()
{
    Serial.print("from anchor 1: ");
    Serial.print(DW1000Ranging.getDistantDevice()->getShortAddress(), HEX);
    Serial.print("\t Range: ");
    Serial.print(DW1000Ranging.getDistantDevice()->getRange());
    Serial.print(" m");
    Serial.print("\t RX power: ");
    Serial.print(DW1000Ranging.getDistantDevice()->getRXPower());
    Serial.println(" dBm");
}

void newRange2()
{
    Serial.print("from anchor 2: ");
    Serial.print(DW2_1000Ranging.getDistantDevice()->getShortAddress(), HEX);
    Serial.print("\t Range: ");
    Serial.print(DW2_1000Ranging.getDistantDevice()->getRange());
    Serial.print(" m");
    Serial.print("\t RX power: ");
    Serial.print(DW2_1000Ranging.getDistantDevice()->getRXPower());
    Serial.println(" dBm");
}

void newDevice(DW1000Device *device)
{
    Serial.print("ranging init; 1 device added ! -> ");
    Serial.print(" short:");
    Serial.println(device->getShortAddress(), HEX);
}

void newDevice2(DW1000Device *device2)
{
    Serial.print("ranging init; 2nd device added ! -> ");
    Serial.print(" short:");
    Serial.println(device2->getShortAddress(), HEX);
}

void inactiveDevice(DW1000Device *device)
{
    Serial.print("delete inactive device from anchor 1: ");
    Serial.println(device->getShortAddress(), HEX);
}

void inactiveDevice2(DW1000Device *device2)
{
    Serial.print("delete inactive device from anchor 2: ");
    Serial.println(device2->getShortAddress(), HEX);
}



// /*

// For ESP32 UWB or ESP32 UWB Pro

// */

// #include <SPI.h>
// #include "DW1000Ranging.h"

// #define ANCHOR_ADD "82:17:5B:D5:A9:9A:E2:9C"
// #define ANCHOR_ADD2 "20:00:00:00:00:9A:E2:9D"

// #define SPI_SCK 18
// #define SPI_MISO 19
// #define SPI_MOSI 23
// #define DW_CS 4

// // connection pins
// const uint8_t PIN_RST = 27; // reset pin
// const uint8_t PIN_IRQ = 34; // irq pin
// const uint8_t PIN_SS = 4;   // spi select pin

// #define SPI_SCK2 33
// #define SPI_MISO2 12
// #define SPI_MOSI2 13
// #define DW_CS2 15

// // connection pins
// const uint8_t PIN_RST2 = 22; // reset pin
// const uint8_t PIN_IRQ2 = 2; // irq pin
// const uint8_t PIN_SS2 = 15;   // spi select pin

// void setup()
// {
//     Serial.begin(115200);
//     delay(1000);
//     //init the configuration
//       SPI.begin(SPI_SCK2, SPI_MISO2, SPI_MOSI2);
//     SPI.begin(SPI_SCK, SPI_MISO, SPI_MOSI);
  
//     DW1000Ranging.initCommunication(PIN_RST, PIN_SS, PIN_IRQ); //Reset, CS, IRQ pin

//     DW2_1000Ranging.initCommunication(PIN_RST2, PIN_SS2, PIN_IRQ2); //Reset, CS, IRQ pin

//     //define the sketch as anchor. It will be great to dynamically change the type of module
//     DW1000Ranging.attachNewRange(newRange);
//     DW1000Ranging.attachBlinkDevice(newBlink);
//     DW1000Ranging.attachInactiveDevice(inactiveDevice);
//     //Enable the filter to smooth the distance
//     //DW1000Ranging.useRangeFilter(true);

//     DW2_1000Ranging.attachNewRange(newRange);
//     DW2_1000Ranging.attachBlinkDevice(newBlink2);
//     DW2_1000Ranging.attachInactiveDevice(inactiveDevice2);

//     //we start the module as an anchor
//     // DW1000Ranging.startAsAnchor("82:17:5B:D5:A9:9A:E2:9C", DW1000.MODE_LONGDATA_RANGE_ACCURACY);

//     DW1000Ranging.startAsAnchor(ANCHOR_ADD, DW1000.MODE_LONGDATA_RANGE_LOWPOWER, false);
//     // DW1000Ranging.startAsAnchor(ANCHOR_ADD, DW1000.MODE_SHORTDATA_FAST_LOWPOWER);
//     // DW1000Ranging.startAsAnchor(ANCHOR_ADD, DW1000.MODE_LONGDATA_FAST_LOWPOWER);
//     // DW1000Ranging.startAsAnchor(ANCHOR_ADD, DW1000.MODE_SHORTDATA_FAST_ACCURACY);
//     // DW1000Ranging.startAsAnchor(ANCHOR_ADD, DW1000.MODE_LONGDATA_FAST_ACCURACY);
//     // DW1000Ranging.startAsAnchor(ANCHOR_ADD, DW1000.MODE_LONGDATA_RANGE_ACCURACY);

//    DW2_1000Ranging.startAsAnchor(ANCHOR_ADD2, DW1000.MODE_LONGDATA_RANGE_LOWPOWER, false);
// }

// void loop()
// {
//     DW1000Ranging.loop();
//     DW2_1000Ranging.loop();
// }

// void newRange()
// {
//     Serial.print("Anchor 1 from: ");
//     Serial.print(DW1000Ranging.getDistantDevice()->getShortAddress(), HEX);
//     Serial.print("\t Range: ");
//     Serial.print(DW1000Ranging.getDistantDevice()->getRange());
//     Serial.print(" m");
//     Serial.print("\t RX power: ");
//     Serial.print(DW1000Ranging.getDistantDevice()->getRXPower());
//     Serial.println(" dBm");
//     //Sensor 2

//     Serial.print("Anchor 2 from: ");
//     Serial.print(DW2_1000Ranging.getDistantDevice()->getShortAddress(), HEX);
//     Serial.print("\t Range: ");
//     Serial.print(DW2_1000Ranging.getDistantDevice()->getRange());
//     Serial.print(" m");
//     Serial.print("\t RX power: ");
//     Serial.print(DW2_1000Ranging.getDistantDevice()->getRXPower());
//     Serial.println(" dBm");
// }

// void newBlink(DW1000Device *device)
// {
//     Serial.print("blink; 1 device added ! -> ");
//     Serial.print(" short:");
//     Serial.println(device->getShortAddress(), HEX);
// }
// void newBlink2(DW1000Device *device)
// {
//     Serial.print("blink; 1 device added ! -> ");
//     Serial.print(" short:");
//     Serial.println(device->getShortAddress(), HEX);
// }

// void inactiveDevice(DW1000Device *device)
// {
//     Serial.print("delete inactive device: ");
//     Serial.println(device->getShortAddress(), HEX);
// }
// void inactiveDevice2(DW1000Device *device)
// {
//     Serial.print("delete inactive device: ");
//     Serial.println(device->getShortAddress(), HEX);
// }