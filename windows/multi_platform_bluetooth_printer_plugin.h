#ifndef FLUTTER_PLUGIN_MULTI_PLATFORM_BLUETOOTH_PRINTER_PLUGIN_H_
#define FLUTTER_PLUGIN_MULTI_PLATFORM_BLUETOOTH_PRINTER_PLUGIN_H_

#include <flutter/method_channel.h>
#include <flutter/plugin_registrar_windows.h>

#include <memory>

namespace multi_platform_bluetooth_printer {

class MultiPlatformBluetoothPrinterPlugin : public flutter::Plugin {
 public:
  static void RegisterWithRegistrar(flutter::PluginRegistrarWindows *registrar);

  MultiPlatformBluetoothPrinterPlugin();

  virtual ~MultiPlatformBluetoothPrinterPlugin();

  // Disallow copy and assign.
  MultiPlatformBluetoothPrinterPlugin(const MultiPlatformBluetoothPrinterPlugin&) = delete;
  MultiPlatformBluetoothPrinterPlugin& operator=(const MultiPlatformBluetoothPrinterPlugin&) = delete;

  // Called when a method is called on this plugin's channel from Dart.
  void HandleMethodCall(
      const flutter::MethodCall<flutter::EncodableValue> &method_call,
      std::unique_ptr<flutter::MethodResult<flutter::EncodableValue>> result);
};

}  // namespace multi_platform_bluetooth_printer

#endif  // FLUTTER_PLUGIN_MULTI_PLATFORM_BLUETOOTH_PRINTER_PLUGIN_H_
