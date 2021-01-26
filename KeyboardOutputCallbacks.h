#ifndef ESP32_BLE_KEYBOARD_OUTPUT_CALLBACKS_H
#define ESP32_BLE_KEYBOARD_OUTPUT_CALLBACKS_H
#include "sdkconfig.h"
#if defined(CONFIG_BT_ENABLED)

#include <BLEServer.h>
#include "BLE2902.h"
#include "BLECharacteristic.h"

// key report back
typedef struct{
        uint8_t bmNumLock : 1;
        uint8_t bmCapsLock : 1;
        uint8_t bmScrollLock : 1;
        uint8_t bmCompose : 1;
        uint8_t bmKana : 1;
        uint8_t bmReserved : 3;
} KbdLeds;
using callBackFunc = void (*)(KbdLeds*);

class KeyboardOutputCallbacks : public BLECharacteristicCallbacks
{
public:
  callBackFunc func; //= [](KbdLeds*){ }
  KeyboardOutputCallbacks(void);
  void onWrite(BLECharacteristic* me);
};
#endif // CONFIG_BT_ENABLED
#endif // ESP32_BLE_KEYBOARD_OUTPUT_CALLBACKS_H
