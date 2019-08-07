#ifndef ESP32_BLE_KEYBOARD_OUTPUT_CALLBACKS_H
#define ESP32_BLE_KEYBOARD_OUTPUT_CALLBACKS_H
#include "sdkconfig.h"
#if defined(CONFIG_BT_ENABLED)

#include <BLEServer.h>
#include "BLE2902.h"
#include "BLECharacteristic.h"

class KeyboardOutputCallbacks : public BLECharacteristicCallbacks
{
public:
  KeyboardOutputCallbacks(void);
  void onWrite(BLECharacteristic* me);
};

#endif // CONFIG_BT_ENABLED
#endif // ESP32_BLE_KEYBOARD_OUTPUT_CALLBACKS_H
