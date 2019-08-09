/**
 * This example turns the ESP32 into a Bluetooth LE keyboard that sends the `a`-key and the `Play/Pause`-key once every 5 seconds.
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
/*
    Serial.println("Pressing the a-key via the Bluetooth keyboard...");
    KeyReport keyReport;
    keyReport.modifiers = 0x00;
    keyReport.reserved = 0x00;
    keyReport.keys[0] = 0x04; // "a"
    keyReport.keys[1] = 0x00;
    keyReport.keys[2] = 0x00;
    keyReport.keys[3] = 0x00;
    keyReport.keys[4] = 0x00;
    keyReport.keys[5] = 0x00;

    bleKeyboard.sendReport(&keyReport); // a-key down

    delay(50);

    KeyReport keyReport2;
    keyReport.modifiers = 0x00;
    keyReport.reserved = 0x00;
    keyReport.keys[0] = 0x00;
    keyReport.keys[1] = 0x00;
    keyReport.keys[2] = 0x00;
    keyReport.keys[3] = 0x00;
    keyReport.keys[4] = 0x00;
    keyReport.keys[5] = 0x00;

    bleKeyboard.sendReport(&keyReport2); // a-key up

    delay(1000)
*/
/*
    Serial.println("Pressing the Play/Pause-key via the Bluetooth keyboard...");

    MediaKeyReport mediaKeyReport;
    mediaKeyReport[0] = 8; // Play/Pause
    mediaKeyReport[1] = 0;
    bleKeyboard.sendReport(&mediaKeyReport); // play/pause-key down (2=MEDIA_KEYS_ID)

    delay(50);

    MediaKeyReport mediaKeyReport2;
    mediaKeyReport2[0] = 0;
    mediaKeyReport2[1] = 0;
    bleKeyboard.sendReport(&mediaKeyReport2); // play/pause-key up (2=MEDIA_KEYS_ID)
*/

    bleKeyboard.write(KEY_MEDIA_PLAY_PAUSE);
    Serial.println("Key sent!");
  }
  delay(5000);
}