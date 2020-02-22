/**
 * This example turns the ESP32 into a Bluetooth LE keyboard and mouse that writes 
 * some words, presses Enter, presses a media key and then Ctrl+Alt+Delete,
 * then moves and the scrolls the mouse and clicks it.
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
  if(keyboard.isConnected()) {
    Serial.println("Sending 'Hello world'");
    keyboard.println("Hello World");

    delay(1000);
    Serial.println("Sending Enter key...");
    keyboard.write(KEY_RETURN);

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
    
    Serial.println("Scroll Down");
    mouse.move(0,0,-1);

    Serial.println("Left click");
    mouse.click(MOUSE_LEFT);
    delay(500);

    Serial.println("Right click");
    mouse.click(MOUSE_RIGHT);
    delay(500);

    Serial.println("Scroll wheel click");
    mouse.click(MOUSE_MIDDLE);
    delay(500);

    Serial.println("Back button click");
    mouse.click(MOUSE_BACK);
    delay(500);

    Serial.println("Forward button click");
    mouse.click(MOUSE_FORWARD);
    delay(500);

    Serial.println("Click left+right mouse button at the same time");
    mouse.click(MOUSE_LEFT | MOUSE_RIGHT);
    delay(500);

    Serial.println("Click left+right mouse button and scroll wheel at the same time");
    mouse.click(MOUSE_LEFT | MOUSE_RIGHT | MOUSE_MIDDLE);
    delay(500);


  }
  
  Serial.println("Waiting 2 seconds...");
  delay(2000);
}
