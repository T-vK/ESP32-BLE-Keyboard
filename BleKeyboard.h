// uncomment the following line to use NimBLE library
//#define USE_NIMBLE

#ifndef ESP32_BLE_KEYBOARD_H
#define ESP32_BLE_KEYBOARD_H
#include "sdkconfig.h"
#if defined(CONFIG_BT_ENABLED)

#if defined(USE_NIMBLE)

#include "NimBLECharacteristic.h"
#include "NimBLEHIDDevice.h"

#define BLEDevice                  NimBLEDevice
#define BLEServerCallbacks         NimBLEServerCallbacks
#define BLECharacteristicCallbacks NimBLECharacteristicCallbacks
#define BLEHIDDevice               NimBLEHIDDevice
#define BLECharacteristic          NimBLECharacteristic
#define BLEAdvertising             NimBLEAdvertising
#define BLEServer                  NimBLEServer

#else

#include "BLEHIDDevice.h"
#include "BLECharacteristic.h"

#endif // USE_NIMBLE

#include "Print.h"

#define BLE_KEYBOARD_VERSION "0.0.4"
#define BLE_KEYBOARD_VERSION_MAJOR 0
#define BLE_KEYBOARD_VERSION_MINOR 0
#define BLE_KEYBOARD_VERSION_REVISION 4

//  Low level key report: up to 6 keys and shift, ctrl etc at once
typedef struct
{
  uint8_t modifiers;
  uint8_t reserved;
  uint8_t keys[6];
} BleKeyReport;

typedef uint8_t BleMediaKeyReport[2];

const BleMediaKeyReport KEY_MEDIA_NEXT_TRACK = {1, 0};
const BleMediaKeyReport KEY_MEDIA_PREVIOUS_TRACK = {2, 0};
const BleMediaKeyReport KEY_MEDIA_STOP = {4, 0};
const BleMediaKeyReport KEY_MEDIA_PLAY_PAUSE = {8, 0};
const BleMediaKeyReport KEY_MEDIA_MUTE = {16, 0};
const BleMediaKeyReport KEY_MEDIA_VOLUME_UP = {32, 0};
const BleMediaKeyReport KEY_MEDIA_VOLUME_DOWN = {64, 0};
const BleMediaKeyReport KEY_MEDIA_WWW_HOME = {128, 0};
const BleMediaKeyReport KEY_MEDIA_LOCAL_MACHINE_BROWSER = {0, 1}; // Opens "My Computer" on Windows
const BleMediaKeyReport KEY_MEDIA_CALCULATOR = {0, 2};
const BleMediaKeyReport KEY_MEDIA_WWW_BOOKMARKS = {0, 4};
const BleMediaKeyReport KEY_MEDIA_WWW_SEARCH = {0, 8};
const BleMediaKeyReport KEY_MEDIA_WWW_STOP = {0, 16};
const BleMediaKeyReport KEY_MEDIA_WWW_BACK = {0, 32};
const BleMediaKeyReport KEY_MEDIA_CONSUMER_CONTROL_CONFIGURATION = {0, 64}; // Media Selection
const BleMediaKeyReport KEY_MEDIA_EMAIL_READER = {0, 128};


class BleKeyboard : public Print, public BLEServerCallbacks, public BLECharacteristicCallbacks
{
private:
  BLEHIDDevice* hid;
  BLECharacteristic* inputKeyboard;
  BLECharacteristic* outputKeyboard;
  BLECharacteristic* inputMediaKeys;
  BLEAdvertising*    advertising;
  BleKeyReport       _keyReport;
  BleMediaKeyReport  _mediaKeyReport;
  std::string        deviceName;
  std::string        deviceManufacturer;
  uint8_t            batteryLevel;
  bool               connected = false;
  uint32_t           _delay_ms = 7;
  void delay_ms(uint64_t ms);

  uint16_t vid       = 0x05ac;
  uint16_t pid       = 0x820a;
  uint16_t version   = 0x0210;

public:
  BleKeyboard(std::string deviceName = "ESP32 Keyboard", std::string deviceManufacturer = "Espressif", uint8_t batteryLevel = 100);
  void begin(void);
  void end(void);
  void sendReport(BleKeyReport* keys);
  void sendReport(BleMediaKeyReport* keys);
  size_t press(uint8_t k);
  size_t press(const BleMediaKeyReport k);
  size_t release(uint8_t k);
  size_t release(const BleMediaKeyReport k);
  size_t write(uint8_t c);
  size_t write(const BleMediaKeyReport c);
  size_t write(const uint8_t *buffer, size_t size);
  void releaseAll(void);
  bool isConnected(void);
  void setBatteryLevel(uint8_t level);
  void setName(std::string deviceName);  
  void setDelay(uint32_t ms);

  void set_vendor_id(uint16_t vid);
  void set_product_id(uint16_t pid);
  void set_version(uint16_t version);
protected:
  virtual void onStarted(BLEServer *pServer) { };
  virtual void onConnect(BLEServer* pServer) override;
  virtual void onDisconnect(BLEServer* pServer) override;
  virtual void onWrite(BLECharacteristic* me) override;

};

#endif // CONFIG_BT_ENABLED
#endif // ESP32_BLE_KEYBOARD_H
