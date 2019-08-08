#include <BLEDevice.h>
#include <BLEUtils.h>
#include <BLEServer.h>
#include "BLE2902.h"
#include "BLEHIDDevice.h"
#include "HIDTypes.h"
#include "HIDKeyboardTypes.h"
#include <driver/adc.h>
#include "sdkconfig.h"

#include "BleConnectionStatus.h"
#include "KeyboardOutputCallbacks.h"
#include "BleKeyboard.h"

#if defined(CONFIG_ARDUHAL_ESP_LOG)
  #include "esp32-hal-log.h"
  #define LOG_TAG ""
#else
  #include "esp_log.h"
  static const char* LOG_TAG = "BLEDevice";
#endif


// Report IDs:
char KEYBOARD_ID = 0x01;
char MEDIA_KEYS_ID = 0x02;

static const uint8_t _hidReportDescriptor[] = {
  USAGE_PAGE(1),      0x01,          // USAGE_PAGE (Generic Desktop Ctrls)
  USAGE(1),           0x06,          // USAGE (Keyboard)
  COLLECTION(1),      0x01,          // COLLECTION (Application)
  // ------------------------------------------------- Keyboard
  REPORT_ID(1),       KEYBOARD_ID,   //   REPORT_ID (1)
  USAGE_PAGE(1),      0x07,          //   USAGE_PAGE (Kbrd/Keypad)
  USAGE_MINIMUM(1),   0xE0,          //   USAGE_MINIMUM (0xE0)
  USAGE_MAXIMUM(1),   0xE7,          //   USAGE_MAXIMUM (0xE7)
  LOGICAL_MINIMUM(1), 0x00,          //   LOGICAL_MINIMUM (0)
  LOGICAL_MAXIMUM(1), 0x01,          //   Logical Maximum (1)
  REPORT_SIZE(1),     0x01,          //   REPORT_SIZE (1)
  REPORT_COUNT(1),    0x08,          //   REPORT_COUNT (8)
  HIDINPUT(1),        0x02,          //   INPUT (Data,Var,Abs,No Wrap,Linear,Preferred State,No Null Position)
  REPORT_COUNT(1),    0x01,          //   REPORT_COUNT (1) ; 1 byte (Reserved)
  REPORT_SIZE(1),     0x08,          //   REPORT_SIZE (8)
  HIDINPUT(1),        0x01,          //   INPUT (Const,Array,Abs,No Wrap,Linear,Preferred State,No Null Position)
  REPORT_COUNT(1),    0x05,          //   REPORT_COUNT (5) ; 5 bits (Num lock, Caps lock, Scroll lock, Compose, Kana)
  REPORT_SIZE(1),     0x01,          //   REPORT_SIZE (1)
  USAGE_PAGE(1),      0x08,          //   USAGE_PAGE (LEDs)
  USAGE_MINIMUM(1),   0x01,          //   USAGE_MINIMUM (0x01) ; Num Lock
  USAGE_MAXIMUM(1),   0x05,          //   USAGE_MAXIMUM (0x05) ; Kana
  HIDOUTPUT(1),       0x02,          //   OUTPUT (Data,Var,Abs,No Wrap,Linear,Preferred State,No Null Position,Non-volatile)
  REPORT_COUNT(1),    0x01,          //   REPORT_COUNT (1) ; 3 bits (Padding)
  REPORT_SIZE(1),     0x03,          //   REPORT_SIZE (3)
  HIDOUTPUT(1),       0x01,          //   OUTPUT (Const,Array,Abs,No Wrap,Linear,Preferred State,No Null Position,Non-volatile)
  REPORT_COUNT(1),    0x06,          //   REPORT_COUNT (6) ; 6 bytes (Keys)
  REPORT_SIZE(1),     0x08,          //   REPORT_SIZE(8)
  LOGICAL_MINIMUM(1), 0x00,          //   LOGICAL_MINIMUM(0)
  LOGICAL_MAXIMUM(1), 0x65,          //   LOGICAL_MAXIMUM(0x65) ; 101 keys
  USAGE_PAGE(1),      0x07,          //   USAGE_PAGE (Kbrd/Keypad)
  USAGE_MINIMUM(1),   0x00,          //   USAGE_MINIMUM (0)
  USAGE_MAXIMUM(1),   0x65,          //   USAGE_MAXIMUM (0x65)
  HIDINPUT(1),        0x00,          //   INPUT (Data,Array,Abs,No Wrap,Linear,Preferred State,No Null Position)
  END_COLLECTION(0),                 // END_COLLECTION
  USAGE_PAGE(1),      0x0C,          // USAGE_PAGE (Consumer)
  USAGE(1),           0x01,          // USAGE (Consumer Control)
  COLLECTION(1),      0x01,          // COLLECTION (Application)
  // ------------------------------------------------- Media Keys
  REPORT_ID(1),       MEDIA_KEYS_ID, //   REPORT_ID (2)
  USAGE_PAGE(1),      0x0C,          //   USAGE_PAGE (Consumer)
  LOGICAL_MINIMUM(1), 0x00,          //   LOGICAL_MINIMUM (0)
  LOGICAL_MAXIMUM(1), 0x01,          //   LOGICAL_MAXIMUM (1)
  REPORT_SIZE(1),     0x01,          //   REPORT_SIZE (1)
  REPORT_COUNT(1),    0x07,          //   REPORT_COUNT (7)
  USAGE(1),           0xB5,          //   USAGE (Scan Next Track)
  USAGE(1),           0xB6,          //   USAGE (Scan Previous Track)
  USAGE(1),           0xB7,          //   USAGE (Stop)
  USAGE(1),           0xB8,          //   USAGE (Eject)
  USAGE(1),           0xCD,          //   USAGE (Play/Pause)
  USAGE(1),           0xE2,          //   USAGE (Mute)
  USAGE(1),           0xE9,          //   USAGE (Volume Increment)
  USAGE(1),           0xEA,          //   USAGE (Volume Decrement)
  HIDINPUT(1),        0x02,          //   INPUT (Data,Var,Abs,No Wrap,Linear,Preferred State,No Null Position)
  END_COLLECTION(0)                  // END_COLLECTION
};

BleKeyboard::BleKeyboard(std::string deviceName, std::string deviceManufacturer, uint8_t batteryLevel) : _buttons(0)
{
  this->deviceName = deviceName;
  this->deviceManufacturer = deviceManufacturer;
  this->batteryLevel = batteryLevel;
  this->connectionStatus = new BleConnectionStatus();
}

void BleKeyboard::begin(void)
{
  xTaskCreate(this->taskServer, "server", 20000, (void *)this, 5, NULL);
}

void BleKeyboard::end(void)
{
}

/*
size_t BleKeyboard::write(uint8_t k)
{

}
size_t BleKeyboard::write(const uint8_t *buffer, size_t size)
{

}
size_t BleKeyboard::press(uint8_t k)
{

}
size_t BleKeyboard::release(uint8_t k)
{

}
void BleKeyboard::releaseAll(void)
{

}
*/

void BleKeyboard::sendReport(KeyReport* keys, char reportId)
{
  if (this->isConnected())
  {
    if (reportId == KEYBOARD_ID)
    {
      this->inputKeyboard->setValue((uint8_t*)keys, sizeof(KeyReport));
      this->inputKeyboard->notify();
    }
    else if (reportId == MEDIA_KEYS_ID)
    {
      this->inputMediaKeys->setValue((uint8_t*)keys, sizeof(MediaKeyReport));
      this->inputMediaKeys->notify();
    }
  }
}

bool BleKeyboard::isConnected(void) {
  return this->connectionStatus->connected;
}

void BleKeyboard::setBatteryLevel(uint8_t level) {
  this->batteryLevel = level;
}

void BleKeyboard::taskServer(void* pvParameter) {
  BleKeyboard* bleKeyboardInstance = (BleKeyboard *) pvParameter; //static_cast<BleKeyboard *>(pvParameter);
  BLEDevice::init(bleKeyboardInstance->deviceName);
  BLEServer *pServer = BLEDevice::createServer();
  pServer->setCallbacks(bleKeyboardInstance->connectionStatus);

  bleKeyboardInstance->hid = new BLEHIDDevice(pServer);
  bleKeyboardInstance->inputKeyboard = bleKeyboardInstance->hid->inputReport(1); // <-- input REPORTID from report map
  bleKeyboardInstance->outputKeyboard = bleKeyboardInstance->hid->outputReport(KEYBOARD_ID);
  bleKeyboardInstance->inputMediaKeys = bleKeyboardInstance->hid->inputReport(MEDIA_KEYS_ID);
  bleKeyboardInstance->connectionStatus->inputKeyboard = bleKeyboardInstance->inputKeyboard;
  bleKeyboardInstance->connectionStatus->outputKeyboard = bleKeyboardInstance->outputKeyboard;

  bleKeyboardInstance->outputKeyboard->setCallbacks(new KeyboardOutputCallbacks());

  bleKeyboardInstance->hid->manufacturer()->setValue(bleKeyboardInstance->deviceManufacturer);

  bleKeyboardInstance->hid->pnp(0x02, 0xe502, 0xa111, 0x0210);
  bleKeyboardInstance->hid->hidInfo(0x00,0x01);

  BLESecurity *pSecurity = new BLESecurity();

  pSecurity->setAuthenticationMode(ESP_LE_AUTH_BOND);

  bleKeyboardInstance->hid->reportMap((uint8_t*)_hidReportDescriptor, sizeof(_hidReportDescriptor));
  bleKeyboardInstance->hid->startServices();

  BLEAdvertising *pAdvertising = pServer->getAdvertising();
  pAdvertising->setAppearance(HID_KEYBOARD);
  pAdvertising->addServiceUUID(bleKeyboardInstance->hid->hidService()->getUUID());
  pAdvertising->start();
  bleKeyboardInstance->hid->setBatteryLevel(bleKeyboardInstance->batteryLevel);

  ESP_LOGD(LOG_TAG, "Advertising started!");
  vTaskDelay(portMAX_DELAY); //delay(portMAX_DELAY);
}
