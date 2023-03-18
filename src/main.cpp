#include <Arduino.h>
#include "NimBLEDevice.h"

void setup() {
  NimBLEDevice::init("Hallo_ich_bin_Fredderich");
    
    NimBLEServer *pServer = NimBLEDevice::createServer();
    NimBLEService *pService = pServer->createService("ABCD");
    NimBLECharacteristic *pCharacteristic = pService->createCharacteristic("1234");
    
    pService->start();
    pCharacteristic->setValue("Hello BLE");
    
    NimBLEAdvertising *pAdvertising = NimBLEDevice::getAdvertising();
    pAdvertising->addServiceUUID("ABCD"); 
    pAdvertising->start(); 
} // End of setup.


// This is the Arduino main loop function.
void loop() {

} // End of loop