#include "KeyboardOutputCallbacks.h"

#if defined(CONFIG_ARDUHAL_ESP_LOG)
  #include "esp32-hal-log.h"
  #define LOG_TAG ""
#else
  #include "esp_log.h"
  static const char* LOG_TAG = "BLEDevice";
#endif

KeyboardOutputCallbacks::KeyboardOutputCallbacks(void) {
}

void KeyboardOutputCallbacks::onWrite(BLECharacteristic* me) {
  KbdLeds* kbled = (KbdLeds*)(me->getValue().c_str());
  ESP_LOGI(LOG_TAG, "special keys: %d", *kbled);
  // if(func!=NULL)
  func(kbled);
}      