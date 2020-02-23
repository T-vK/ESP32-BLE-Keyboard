#include "BleConnectionStatus.h"

BleConnectionStatus::BleConnectionStatus(void) {
}

void BleConnectionStatus::onConnect(BLEServer* pServer)
{
  this->connected = true;
  BLE2902* desc = (BLE2902*)this->inputKeyboard->getDescriptorByUUID(BLEUUID((uint16_t)0x2902));
  desc->setNotifications(true);

  desc = (BLE2902*)this->inputMediaKeys->getDescriptorByUUID(BLEUUID((uint16_t)0x2902));
  desc->setNotifications(true);
}

void BleConnectionStatus::onDisconnect(BLEServer* pServer)
{
  this->connected = false;
  BLE2902* desc = (BLE2902*)this->inputKeyboard->getDescriptorByUUID(BLEUUID((uint16_t)0x2902));
  desc->setNotifications(false);

  desc = (BLE2902*)this->inputMediaKeys->getDescriptorByUUID(BLEUUID((uint16_t)0x2902));
  desc->setNotifications(false);

}
