#ifndef BLE_PLUGIN_H
#define BLE_PLUGIN_H

#include <bluez/bluetooth/bluetooth.h>
#include <bluez/hci/hci.h>
#include <bluez/gatt/gatt.h>

class BlePlugin {
public:
  BlePlugin();
  ~BlePlugin();

  void startScanning(GattDeviceFoundCallback callback);
  void stopScanning();

  void connect(bdaddr_t address);
  void disconnect();

  void writeData(uint8_t *data, size_t length);

private:
  bt_hci_adapter *adapter;
  bt_gatt_device *device;
  bt_gatt_service *service;
  bt_gatt_characteristic *characteristic;

  bt_uuid_t service_uuid;
  bt_uuid_t char_uuid;
};

#endif // BLE_PLUGIN_H