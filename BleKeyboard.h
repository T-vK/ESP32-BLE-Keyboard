#ifndef ESP32_BLE_KEYBOARD_H
#define ESP32_BLE_KEYBOARD_H
#include "sdkconfig.h"
#if defined(CONFIG_BT_ENABLED)

#include "BleConnectionStatus.h"
#include "BLEHIDDevice.h"
#include "BLECharacteristic.h"

//  Low level key report: up to 6 keys and shift, ctrl etc at once
typedef struct
{
  uint8_t modifiers;
  uint8_t reserved;
  uint8_t keys[6];
} KeyReport;

typedef uint8_t MediaKeyReport[2];

class BleKeyboard {
private:
  uint8_t _buttons;
  BleConnectionStatus* connectionStatus;
  BLEHIDDevice* hid;
  BLECharacteristic* inputKeyboard;
  BLECharacteristic* outputKeyboard;
  BLECharacteristic* inputMediaKeys;
  KeyReport _keyReport;
  MediaKeyReport _mediaKeyReport;
  void buttons(uint8_t b);
  static void taskServer(void* pvParameter);
public:
  BleKeyboard(std::string deviceName = "ESP32 Bluetooth Keyboard", std::string deviceManufacturer = "Espressif", uint8_t batteryLevel = 100);
  void begin(void);
  void end(void);
  void sendReport(KeyReport* keys, char reportId=1);
  //size_t write(uint8_t k);
  //size_t write(const uint8_t *buffer, size_t size);
  //size_t press(uint8_t k);
  //size_t release(uint8_t k);
  //void releaseAll(void);
  bool isConnected(void);
  void setBatteryLevel(uint8_t level);
  uint8_t batteryLevel;
  std::string deviceManufacturer;
  std::string deviceName;
};

#endif // CONFIG_BT_ENABLED
#endif // ESP32_BLE_KEYBOARD_H
