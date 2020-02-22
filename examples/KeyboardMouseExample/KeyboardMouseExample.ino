/**
 * This example turns the ESP32 into a Bluetooth LE keyboard and mouse that writes 
 * the words, presses Enter, presses a media key and then Ctrl+Alt+Delete,
 * then moves the mouse and clicks it.
 */
 
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
  static int i = 0;
  if(keyboard.isConnected()) {
    Serial.println("Sending 'Hi Mom'...");
    keyboard.printf("Hi Mom =1234567890-\\;',./`[]  +!@#$%%^&*()_|:\"<>?~{} %d", i++);

    Serial.println("Sending Enter key...");
    keyboard.write(KEY_RETURN);

/*
    delay(1000);
    Serial.println("Sending Play/Pause media key...");
    keyboard.write(KEY_MEDIA_PLAY_PAUSE);

    delay(1000);

    Serial.println("Sending Ctrl+Alt+Delete...");
    keyboard.press(KEY_LEFT_CTRL);
    keyboard.press(KEY_LEFT_ALT);
    keyboard.press(KEY_DELETE);
    delay(100);
    keyboard.releaseAll();
*/

    unsigned long startTime;

    Serial.println("Move mouse pointer up");
    startTime = millis();
    while(millis()<startTime+1000) {
      mouse.move(0,-1);
      delay(5);
    }
    Serial.println("Move mouse pointer left");
    startTime = millis();
    while(millis()<startTime+1000) {
      mouse.move(-1,0);
      delay(5);
    }

    Serial.println("Move mouse pointer down");
    startTime = millis();
    while(millis()<startTime+1000) {
      mouse.move(0,1);
      delay(5);
    }

    Serial.println("Move mouse pointer right");
    startTime = millis();
    while(millis()<startTime+1000) {
      mouse.move(1,0);
      delay(5);
    }

  }

  Serial.println("Waiting 2 seconds...");
  delay(2000);
}
