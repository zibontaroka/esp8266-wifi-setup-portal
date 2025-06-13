#include <Arduino.h>
#include "WiFiSetup.h"

// Project-specific credentials
const char* apSSID = "MyIoT_Device";
const char* apPassword = "12345678";

WiFiSetup wifiSetup(apSSID, apPassword);

void setup() {
  Serial.begin(115200);
  delay(1000);
  wifiSetup.begin();
}

void loop() {
  wifiSetup.handle();
}
