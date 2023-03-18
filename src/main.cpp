#include <Arduino.h>
#include "NimBLEDevice.h"

void setup() {
    NimBLEDevice::init("NimBLE");
    NimBLEServer *pServer = NimBLEDevice::createServer();
    NimBLEService *pService = pServer->createService("ABCD");
} // End of setup.


// This is the Arduino main loop function.
void loop() {

} // End of loop