# ESP32 BLE Keyboard library

This library allows you to make the ESP32 act as a Bluetooth Keyboard and control what it does.

Warning: This library is not ready yet. Atm keys can only be sent using the `sendReport` method.
The code hasn't been tested at all. It should compile wihtout errors though.

## Installation
- (Make sure you can use the ESP32 with the Arduino IDE. [Instructions can be found here.](https://github.com/espressif/arduino-esp32#installation-instructions))
- [Download the latest release of this library from the release page.](https://github.com/T-vK/ESP32-BLE-Keyboard/releases)
- In the Arduino IDE go to "Sketch" -> "Include Library" -> "Add .ZIP Library..." and select the file you just downloaded.
- You can now go to "File" -> "Examples" -> "ESP32 BLE Keyboard" and select any of the examples to get started.

## Example

``` C++
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
```

## API docs
The BleKeyboard interface is almost identical to the Keyboard Interface, so you can use documentation right here:
https://www.arduino.cc/reference/en/language/functions/usb/keyboard/

Just remember that you have to use `bleKeyboard` instead of just `Keyboard` and you need these two lines at the top of your script:
```
#include <BleKeyboard.h>
BleKeyboard bleKeyboard;
```

## Credits

Credits to [chegewara](https://github.com/chegewara) as this library is based on [this piece of code](https://github.com/nkolban/esp32-snippets/issues/230#issuecomment-473135679) that he provided.