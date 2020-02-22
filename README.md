# ESP32 BLE Combo Keyboard & Mouse library

This library allows you to make the ESP32 act as a Bluetooth keyboard and mouse with Arduino.

You might also be interested in:

- [ESP32-BLE-Mouse](https://github.com/T-vK/ESP32-BLE-Mouse)
- [ESP32-BLE-Keyboard](https://github.com/T-vK/ESP32-BLE-Keyboard)
- [ESP32-BLE-Gamepad](https://github.com/lemmingDev/ESP32-BLE-Gamepad)


## Todo:

 - [ ] Read Numlock/Capslock/Scrolllock state

## Installation
- (Make sure you can use the ESP32 with the Arduino IDE. [Instructions can be found here.](https://github.com/espressif/arduino-esp32#installation-instructions))
- [Download the latest release of this library from the release page.](https://github.com/T-vK/ESP32-BLE-Keyboard/releases)
- In the Arduino IDE go to "Sketch" -> "Include Library" -> "Add .ZIP Library..." and select the file you just downloaded.
- You can now go to "File" -> "Examples" -> "ESP32 BLE Combo" and select any of the examples to get started.

## Example

```
#include <BleComboKeyboard.h>
#include <BleComboMouse.h>

BleComboKeyboard keyboard;
BleComboMouse mouse(&keyboard);

void setup() {
  Serial.begin(115200);
  Serial.println("Starting work!");
  keyboard.begin();
  mouse.begin();
}

void loop() {
  if(keyboard.isConnected()) {
    Serial.println("Sending 'Hello world'");
    keyboard.println("Hello World");

    Serial.println("Sending Enter key...");
    keyboard.write(KEY_RETURN);

    Serial.println("Sending Play/Pause media key...");
    keyboard.write(KEY_MEDIA_PLAY_PAUSE);

    Serial.println("Sending Ctrl+Alt+Delete...");
    keyboard.press(KEY_LEFT_CTRL);
    keyboard.press(KEY_LEFT_ALT);
    keyboard.press(KEY_DELETE);
    delay(100);
    keyboard.releaseAll();

    Serial.println("Move mouse pointer up");
    mouse.move(0,-10);
    
    Serial.println("Scroll Down");
    mouse.move(0,0,-1);

    Serial.println("Left click");
    mouse.click(MOUSE_LEFT);
  }
  
  Serial.println("Waiting 2 seconds...");
  delay(2000);
}

```
## Credits

This is fork of @T-kV's excellent [ESP32-BLE-Mouse](https://github.com/T-vK/ESP32-BLE-Mouse)
and [ESP32-BLE-Keyboard](https://github.com/T-vK/ESP32-BLE-Keyboard) libraries.
