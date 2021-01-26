/**
 * This example turns the ESP32 into a Bluetooth LE keyboard that you can use num/caps/scroll lock led for some reason ex:  turn your room light by scroll lock :))) 
 */
#include <BleKeyboard.h>

BleKeyboard bleKeyboard;

//note that this function should run "fast" or esp will crash
void KbdLedCb(KbdLeds *kbls)
{
    digitalWrite(2,kbls->bmNumLock);
    // digitalWrite(2,kbls->bmCapsLock);
    // digitalWrite(2,kbls->bmScrollLock);
    // ...
}

void setup() {
  pinMode(2,OUTPUT);
  Serial.begin(115200);
  Serial.println("Starting BLE work!");     
  bleKeyboard.begin();
  delay(1000);//must have delay for the BLE  finish inital
  bleKeyboard.setLedChangeCallBack(KbdLedCb);
}

void loop() {
  bleKeyboard.write(KEY_NUM_LOCK);
  delay(10000);
}
