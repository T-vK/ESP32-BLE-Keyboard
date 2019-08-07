/**
 * This example turns the ESP32 into a Bluetooth LE keyboard that types the letter `a` once every 5 seconds.
 */
#include <BleKeyboard.h>

BleKeyboard bleKeyboard;

void setup() {
  Serial.begin(115200);
  Serial.println("Starting BLE work!");
  bleKeyboard.begin();
}

void loop() {
  if(bleKeyboard.isConnected()) {
    Serial.println("Pressing the a-key via the Bluetooth keyboard");

    KeyReport keyReport;
    keyReport.modifiers = 0x00;
    keyReport.reserved = 0x00;
    keyReport.keys[0] = 0x61; // a-key
    keyReport.keys[0] = 0x00;
    keyReport.keys[0] = 0x00;
    keyReport.keys[0] = 0x00;
    keyReport.keys[0] = 0x00;
    keyReport.keys[0] = 0x00;

    bleKeyboard.sendReport(&keyReport); // a-key down

    delay(50);

    KeyReport keyReport2;
    keyReport.modifiers = 0x00;
    keyReport.reserved = 0x00;
    keyReport.keys[0] = 0x00;
    keyReport.keys[0] = 0x00;
    keyReport.keys[0] = 0x00;
    keyReport.keys[0] = 0x00;
    keyReport.keys[0] = 0x00;
    keyReport.keys[0] = 0x00;

    bleKeyboard.sendReport(&keyReport2); // a-key up

  }
  delay(5000);
}