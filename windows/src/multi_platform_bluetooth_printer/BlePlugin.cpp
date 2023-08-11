#include "BlePlugin.h"

BlePlugin::BlePlugin(IInspectable *context) {
  // Get BluetoothAdapter instance
  bluetoothAdapter = BluetoothAdapter::GetDefault();

  // Create GattDeviceWatcher
  gattDeviceWatcher = GattDeviceWatcher::Create(bluetoothAdapter);

  // Create GattConnection
  gattConnection = nullptr;

  // Create GattCharacteristic
  gattCharacteristic = nullptr;

  // Create UUID objects
  serviceUuid = UUID::FromString(L"00001800-0000-1000-8000-00805f9b34fb");
  charUuid = UUID::FromString(L"00002a01-0000-1000-8000-00805f9b34fb");

  // Set up GATT client connection state change callback
  gattCallback = ref new GattDeviceWatcherCallback(this, &BlePlugin::onGattDeviceWatcherStatusChanged);
}

void BlePlugin::startScanning(GattDeviceWatcherCallback *scanCallback) {
  // Set the GATT client connection state change callback
  gattDeviceWatcher->DeviceWatcherStatusChanged(scanCallback);

  // Start scanning for devices
  gattDeviceWatcher->Start();
}

void BlePlugin::stopScanning(GattDeviceWatcherCallback *scanCallback) {
  // Stop scanning for devices
  gattDeviceWatcher->Stop();
}

void BlePlugin::connect(String address) {
  // Create a BluetoothDevice object from the address
  BluetoothDevice device = BluetoothDevice::FromIdAsync(address).get();

  // Connect to the device
  gattConnection = device.ConnectAsync().get();

  // Wait for the connection to be established
  while (!gattConnection->IsConnected()) {
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
  }

  // Get the service with the specified UUID
  GattService service = gattConnection->GetService(serviceUuid);

  // Get the characteristic with the specified UUID
  gattCharacteristic = service.GetCharacteristic(charUuid);
}

void BlePlugin::disconnect() {
  // Disconnect from the device
  gattConnection->Disconnect();
}

void BlePlugin::writeData(ByteArray data) {
  // Write the data to the characteristic
  gattCharacteristic->WriteValueAsync(data).get();
}

void BlePlugin::onGattDeviceWatcherStatusChanged(GattDeviceWatcher *watcher, GattDeviceWatcherStatus status) {
  // Handle the GATT client connection state change
  switch (status) {
    case GattDeviceWatcherStatus::DeviceFound: {
      // A device was found
      break;
    }
    case GattDeviceWatcherStatus::DeviceScanningCompleted: {
      // Scanning for devices is complete
      break;
    }
    case GattDeviceWatcherStatus::DevicePairingRequired: {
      // The device requires pairing
      break;
    }
  }
}
