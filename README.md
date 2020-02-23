# ESP32 BLE Combo Keyboard & Mouse library

This library allows you to make the ESP32 act as a Bluetooth keyboard and mouse with Arduino.

## Todo

 - [ ] Read Numlock/Capslock/Scrolllock state
 - [ ] Add gamepad support
 - [x] Auto-instantiate Keyboard, Mouse objects (like the standard Arduino libraries)
 - [ ] Optimize so that only needed classes get created for BLE.

## Installation
- (Make sure you can use the ESP32 with the Arduino IDE. [Instructions can be found here.](https://github.com/espressif/arduino-esp32#installation-instructions))
- [Download the latest release of this library from the release page.](https://github.com/T-vK/ESP32-BLE-Keyboard/releases)
- In the Arduino IDE go to "Sketch" -> "Include Library" -> "Add .ZIP Library..." and select the file you just downloaded.
- You can now go to "File" -> "Examples" -> "ESP32 BLE Combo" and select any of the examples to get started.

## Example

```
#include <BleCombo.h>

void setup() {
  Serial.begin(115200);
  Serial.println("Starting work!");
  Keyboard.begin();
  Mouse.begin();
}

void loop() {
  if(Keyboard.isConnected()) {
    Serial.println("Sending 'Hello world'");
    Keyboard.println("Hello World");

    Serial.println("Sending Enter key...");
    Keyboard.write(KEY_RETURN);

    Serial.println("Sending Play/Pause media key...");
    Keyboard.write(KEY_MEDIA_PLAY_PAUSE);

    Serial.println("Sending Ctrl+Alt+Delete...");
    Keyboard.press(KEY_LEFT_CTRL);
    Keyboard.press(KEY_LEFT_ALT);
    Keyboard.press(KEY_DELETE);
    delay(100);
    Keyboard.releaseAll();

    Serial.println("Move mouse pointer up");
    Mouse.move(0,-10);
    
    Serial.println("Scroll Down");
    Mouse.move(0,0,-1);

    Serial.println("Left click");
    Mouse.click(MOUSE_LEFT);
  }
  
  Serial.println("Waiting 2 seconds...");
  delay(2000);
}

```
## Credits

This is fork of @T-kV's excellent [ESP32-BLE-Mouse](https://github.com/T-vK/ESP32-BLE-Mouse)
and [ESP32-BLE-Keyboard](https://github.com/T-vK/ESP32-BLE-Keyboard) libraries.

You might also be interested in:

- [ESP32-BLE-Mouse](https://github.com/T-vK/ESP32-BLE-Mouse)
- [ESP32-BLE-Keyboard](https://github.com/T-vK/ESP32-BLE-Keyboard)
- [ESP32-BLE-Gamepad](https://github.com/lemmingDev/ESP32-BLE-Gamepad)

