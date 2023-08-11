// BlePlugin.h

#pragma once

#include <functional>
#include <string>

typedef std::function<void(const gchar*)> DeviceCallback; 

class BlePlugin {

public:

  BlePlugin(GDBusConnection* connection);
  ~BlePlugin();

  void startScanning(DeviceCallback callback);
  void stopScanning();

  void connect(const std::string& address);
  void disconnect();

  void writeData(const uint8_t* data, size_t length);

private:

  void init_bluez();

  GDBusConnection* connection;
  GDBusProxy* adapter_proxy;

  DeviceCallback scan_callback;

};