#ifndef BLEPLUGIN_H
#define BLEPLUGIN_H

#include <winrt/Windows.Devices.Bluetooth.h>
#include <winrt/Windows.Devices.Bluetooth.GenericAttributeProfile.h>
#include <winrt/Windows.Foundation.h>

using namespace winrt;
using namespace Windows::Devices::Bluetooth;
using namespace Windows::Devices::Bluetooth::GenericAttributeProfile;

class BlePlugin {
public:
  BlePlugin(IInspectable *context);

  // Callback for GATT client connection state changes
  private GattDeviceWatcherCallback gattCallback;

  // Start and stop scanning
  void startScanning(GattDeviceWatcherCallback *scanCallback);
  void stopScanning(GattDeviceWatcherCallback *scanCallback);

  // Connect to device
  void connect(String address);

  // Disconnect GATT client
  void disconnect();

  // Write data to characteristic
  void writeData(ByteArray data);

private:
  IBluetoothAdapter *bluetoothAdapter;
  GattDeviceWatcher *gattDeviceWatcher;
  GattConnection *gattConnection;
  GattCharacteristic *gattCharacteristic;
  UUID *serviceUuid;
  UUID *charUuid;
};

#endif // BLEPLUGIN_H
