// uncomment the following line to use NimBLE library
//#define USE_NIMBLE

#ifndef ESP32_BLE_KEYBOARD_H
#define ESP32_BLE_KEYBOARD_H
//#pragma message ("Supressing Bluethoot Warning: 'BT: forcing BR/EDR max sync conn eff to 1 (Bluedroid HFP requires SCO/eSCO)'")
//#pragma warning( push )
//#pragma warning (disable : 4068 ) /* disable unknown pragma warnings. especially the Bluthoot onces */
#include "sdkconfig.h"
#if defined(CONFIG_BT_ENABLED)

#if defined(USE_NIMBLE)

#include "NimBLECharacteristic.h"
#include "NimBLEHIDDevice.h"
#include "NimBLEAdvertising.h"
#include "NimBLEServer.h"
#include "NimBLECharacteristic.h"

#define BLEDevice                   NimBLEDevice
#define BLEServerCallbacks          NimBLEServerCallbacks
#define BLECharacteristicCallbacks  NimBLECharacteristicCallbacks
#define BLEHIDDevice                NimBLEHIDDevice
#define BLECharacteristic           NimBLECharacteristic
#define BLEAdvertising              NimBLEAdvertising
#define BLEServer                   NimBLEServer
#define setScanResponse             setScanResponseData
#define hidService                  getHidService
#define inputReport                 getInputReport
#define outputReport                getOutputReport
//#define manufacturer()->setValue(    setManufacturer
#define hidInfo                     setHidInfo
#define pnp                         setPnp
#define reportMap                   setReportMap

#else

#include "BLEHIDDevice.h"
#include "BLECharacteristic.h"

#endif // USE_NIMBLE

//#include "Print.h"

#define BLE_KEYBOARD_VERSION "0.0.4"
#define BLE_KEYBOARD_VERSION_MAJOR 0
#define BLE_KEYBOARD_VERSION_MINOR 0
#define BLE_KEYBOARD_VERSION_REVISION 4

#define KEY_LEFT_CTRL (uint8_t) 0x80
#define KEY_LEFT_SHIFT (uint8_t) 0x81
#define KEY_LEFT_ALT (uint8_t) 0x82
#define KEY_LEFT_GUI (uint8_t) 0x83
#define KEY_RIGHT_CTRL (uint8_t) 0x84
#define KEY_RIGHT_SHIFT (uint8_t) 0x85
#define KEY_RIGHT_ALT (uint8_t) 0x86
#define KEY_RIGHT_GUI (uint8_t) 0x87

#define KEY_UP_ARROW (uint8_t) 0xDA
#define KEY_DOWN_ARROW (uint8_t) 0xD9
#define KEY_LEFT_ARROW (uint8_t) 0xD8
#define KEY_RIGHT_ARROW (uint8_t) 0xD7
#define KEY_BACKSPACE (uint8_t) 0xB2
#define KEY_TAB (uint8_t) 0xB3
#define KEY_RETURN (uint8_t) 0xB0
#define KEY_ESC (uint8_t) 0xB1
#define KEY_INSERT (uint8_t) 0xD1
#define KEY_PRTSC (uint8_t) 0xCE
#define KEY_DELETE (uint8_t) 0xD4
#define KEY_PAGE_UP (uint8_t) 0xD3
#define KEY_PAGE_DOWN (uint8_t) 0xD6
#define KEY_HOME (uint8_t) 0xD2
#define KEY_END (uint8_t) 0xD5
#define KEY_CAPS_LOCK (uint8_t) 0xC1
#define KEY_F1 (uint8_t) 0xC2
#define KEY_F2 (uint8_t) 0xC3
#define KEY_F3 (uint8_t) 0xC4
#define KEY_F4 (uint8_t) 0xC5
#define KEY_F5 (uint8_t) 0xC6
#define KEY_F6 (uint8_t) 0xC7
#define KEY_F7 (uint8_t) 0xC8
#define KEY_F8 (uint8_t) 0xC9
#define KEY_F9 (uint8_t) 0xCA
#define KEY_F10 (uint8_t) 0xCB
#define KEY_F11 (uint8_t) 0xCC
#define KEY_F12 (uint8_t) 0xCD
#define KEY_F13 (uint8_t) 0xF0
#define KEY_F14 (uint8_t) 0xF1
#define KEY_F15 (uint8_t) 0xF2
#define KEY_F16 (uint8_t) 0xF3
#define KEY_F17 (uint8_t) 0xF4
#define KEY_F18 (uint8_t) 0xF5
#define KEY_F19 (uint8_t) 0xF6
#define KEY_F20 (uint8_t) 0xF7
#define KEY_F21 (uint8_t) 0xF8
#define KEY_F22 (uint8_t) 0xF9
#define KEY_F23 (uint8_t) 0xFA
#define KEY_F24 (uint8_t) 0xFB

#define KEY_NUM_0 (uint8_t) 0xEA
#define KEY_NUM_1 (uint8_t) 0xE1
#define KEY_NUM_2 (uint8_t) 0xE2
#define KEY_NUM_3 (uint8_t) 0xE3
#define KEY_NUM_4 (uint8_t) 0xE4
#define KEY_NUM_5 (uint8_t) 0xE5
#define KEY_NUM_6 (uint8_t) 0xE6
#define KEY_NUM_7 (uint8_t) 0xE7
#define KEY_NUM_8 (uint8_t) 0xE8
#define KEY_NUM_9 (uint8_t) 0xE9
#define KEY_NUM_SLASH (uint8_t) 0xDC
#define KEY_NUM_ASTERISK (uint8_t) 0xDD
#define KEY_NUM_MINUS (uint8_t) 0xDE
#define KEY_NUM_PLUS (uint8_t) 0xDF
#define KEY_NUM_ENTER (uint8_t) 0xE0
#define KEY_NUM_PERIOD (uint8_t) 0xEB

typedef uint8_t MediaKeyReport[2];

const MediaKeyReport KEY_MEDIA_NEXT_TRACK = {1, 0};
const MediaKeyReport KEY_MEDIA_PREVIOUS_TRACK = {2, 0};
const MediaKeyReport KEY_MEDIA_STOP = {4, 0};
const MediaKeyReport KEY_MEDIA_PLAY_PAUSE = {8, 0};
const MediaKeyReport KEY_MEDIA_MUTE = {16, 0};
const MediaKeyReport KEY_MEDIA_VOLUME_UP = {32, 0};
const MediaKeyReport KEY_MEDIA_VOLUME_DOWN = {64, 0};
const MediaKeyReport KEY_MEDIA_WWW_HOME = {128, 0};
const MediaKeyReport KEY_MEDIA_LOCAL_MACHINE_BROWSER = {0, 1}; // Opens "My Computer" on Windows
const MediaKeyReport KEY_MEDIA_CALCULATOR = {0, 2};
const MediaKeyReport KEY_MEDIA_WWW_BOOKMARKS = {0, 4};
const MediaKeyReport KEY_MEDIA_WWW_SEARCH = {0, 8};
const MediaKeyReport KEY_MEDIA_WWW_STOP = {0, 16};
const MediaKeyReport KEY_MEDIA_WWW_BACK = {0, 32};
const MediaKeyReport KEY_MEDIA_CONSUMER_CONTROL_CONFIGURATION = {0, 64}; // Media Selection
const MediaKeyReport KEY_MEDIA_EMAIL_READER = {0, 128};


//  Low level key report: up to 6 keys and shift, ctrl etc at once
typedef struct
{
  uint8_t modifiers;
  uint8_t reserved;
  uint8_t keys[6];
} KeyReport;

class BleKeyboard : public Print, public BLEServerCallbacks, public BLECharacteristicCallbacks
{
private:
  BLEHIDDevice* hid;
  BLECharacteristic* inputKeyboard;
  BLECharacteristic* outputKeyboard;
  BLECharacteristic* inputMediaKeys;
  BLEAdvertising*    advertising;
  KeyReport          _keyReport;
  MediaKeyReport     _mediaKeyReport;
  #if defined(USE_NIMBLE)
  std::string              deviceName;
  std::string              deviceManufacturer;
  #else
  String              deviceName;
  String              deviceManufacturer;
  #endif
  uint8_t            batteryLevel;
  bool               connected = false;
  uint32_t           _delay_ms = 7;
  void delay_ms(uint64_t ms);

  uint16_t vid       = 0x05ac;
  uint16_t pid       = 0x820a;
  uint16_t version   = 0x0210;

public:
#if defined(USE_NIMBLE)
  BleKeyboard(std::string deviceName = "ESP32 Keyboard", std::string deviceManufacturer = "Espressif", uint8_t batteryLevel = 100);
#else
  BleKeyboard(String deviceName = "ESP32 Keyboard", String deviceManufacturer = "Espressif", uint8_t batteryLevel = 100);
#endif
  void begin(void);
  void end(void);
  void sendReport(KeyReport* keys);
  void sendReport(MediaKeyReport* keys);
  size_t press(uint8_t k);
  size_t press(const MediaKeyReport k);
  size_t release(uint8_t k);
  size_t release(const MediaKeyReport k);
  size_t write(uint8_t c);
  size_t write(const MediaKeyReport c);
  size_t write(const uint8_t *buffer, size_t size);
  void releaseAll(void);
  bool isConnected(void);
  void setBatteryLevel(uint8_t level);
#if defined(USE_NIMBLE)
  void setName(std::string deviceName);  
#else
  void setName(String deviceName);  
#endif
  void setDelay(uint32_t ms);

  void set_vendor_id(uint16_t vid);
  void set_product_id(uint16_t pid);
  void set_version(uint16_t version);
protected:
  virtual void onStarted(BLEServer *pServer) { };
  #ifndef USE_NIMBLE
  virtual void onConnect(BLEServer* pServer) override;
  virtual void onDisconnect(BLEServer* pServer) override;
  virtual void onWrite(BLECharacteristic* me) override;
  #else 
  //Nimble got some more stuff
  virtual void onConnect(BLEServer* pServer, NimBLEConnInfo& connInfo) override;
  virtual void onDisconnect(BLEServer* pServer, NimBLEConnInfo& connInfo, int reason) override;
  virtual void onWrite(BLECharacteristic* me, NimBLEConnInfo& connInfo) override;
  #endif
};

#endif // CONFIG_BT_ENABLED
//#pragma warning( pop )
#endif // ESP32_BLE_KEYBOARD_H
