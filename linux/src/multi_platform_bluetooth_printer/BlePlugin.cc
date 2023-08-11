#include <bluez/bluetooth/bluetooth.h>
#include <bluez/hci/hci.h>
#include <bluez/gatt/gatt.h>

class BlePlugin {
public:
  BlePlugin() {
    adapter = hci_open_dev(HCI_DEV_ID);
    device = NULL;
    characteristic = NULL;

    // Create UUID objects
    service_uuid = bluetooth_uuid_from_string("00001800-0000-1000-8000-00805f9b34fb");
    char_uuid = bluetooth_uuid_from_string("00002a01-0000-1000-8000-00805f9b34fb");
  }

  ~BlePlugin() {
    if (device)
      gatt_device_unref(device);
    hci_close_dev(adapter);
  }

  void startScanning(GattDeviceFoundCallback callback) {
    gatt_adapter_scan_start(adapter, callback);
  }

  void stopScanning() {
    gatt_adapter_scan_stop(adapter);
  }

  void connect(bdaddr_t address) {
    device = gatt_adapter_get_device(adapter, address);
    gatt_device_connect(device, NULL, NULL, NULL);

    // Wait for connection
    // ...

    service = gatt_device_get_service(device, service_uuid);
    characteristic = gatt_service_get_characteristic(service, char_uuid);
  }

  void disconnect() {
    gatt_device_disconnect(device);
  }

  void writeData(uint8_t *data, size_t length) {
    gatt_characteristic_write_value(characteristic, data, length);
  }

private:
  bt_hci_adapter *adapter;
  bt_gatt_device *device;
  bt_gatt_service *service;
  bt_gatt_characteristic *characteristic;

  bt_uuid_t service_uuid;
  bt_uuid_t char_uuid;
};