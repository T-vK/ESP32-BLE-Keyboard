#include <Arduino.h>
#include <BleKeyboard.h>

BleKeyboard bleKeyboard("ESP32 Keyboard");

void setup() {
  bleKeyboard.begin();
}

void loop() {
  if (bleKeyboard.isConnected()) {
    bleKeyboard.print("Hello");
  }
}
