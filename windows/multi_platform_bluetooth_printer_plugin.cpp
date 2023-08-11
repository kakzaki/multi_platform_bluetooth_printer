#include "multi_platform_bluetooth_printer_plugin.h"

// This must be included before many other Windows headers.
#include <windows.h>

// For getPlatformVersion; remove unless needed for your plugin implementation.
#include <VersionHelpers.h>

#include <flutter/method_channel.h>
#include <flutter/plugin_registrar_windows.h>
#include <flutter/standard_method_codec.h>

#include <memory>
#include <sstream>

#include "BlePlugin.h"

namespace multi_platform_bluetooth_printer {

// static
void MultiPlatformBluetoothPrinterPlugin::RegisterWithRegistrar(
    flutter::PluginRegistrarWindows *registrar) {
  auto channel =
      std::make_unique<flutter::MethodChannel<flutter::EncodableValue>>(
          registrar->messenger(), "multi_platform_bluetooth_printer",
          &flutter::StandardMethodCodec::GetInstance());

  auto plugin = std::make_unique<MultiPlatformBluetoothPrinterPlugin>();
  plugin->blePlugin = new BlePlugin(registrar->GetNativeHandle());

  channel->SetMethodCallHandler(
      [plugin_pointer = plugin.get()](const auto &call, auto result) {
        plugin_pointer->HandleMethodCall(call, std::move(result));
      });

  registrar->AddPlugin(std::move(plugin));
}

MultiPlatformBluetoothPrinterPlugin::MultiPlatformBluetoothPrinterPlugin() {}

MultiPlatformBluetoothPrinterPlugin::~MultiPlatformBluetoothPrinterPlugin() {}

void MultiPlatformBluetoothPrinterPlugin::HandleMethodCall(
    const flutter::MethodCall<flutter::EncodableValue> &method_call,
    std::unique_ptr<flutter::MethodResult<flutter::EncodableValue>> result) {
   if (method_call.method_name().compare("startScanning") == 0) {
    blePlugin->startScanning();
    result->Success(flutter::EncodableValue(true));
  } else if (method_call.method_name().compare("stopScanning") == 0) {
    blePlugin->stopScanning();
    result->Success(flutter::EncodableValue(true));
  } else if (method_call.method_name().compare("connect") == 0) {
    const auto arguments = method_call.arguments();
    const auto address = arguments["address"].GetString();
    blePlugin->connect(address);
    result->Success(flutter::EncodableValue(true));
  } else if (method_call.method_name().compare("disconnect") == 0) {
    blePlugin->disconnect();
    result->Success(flutter::EncodableValue(true));
  } else if (method_call.method_name().compare("writeData") == 0) {
    const auto arguments = method_call.arguments();
    const auto data = arguments["data"].GetByteArray();
    blePlugin->writeData(data);
    result->Success(flutter::EncodableValue(true));
  } else {
    result->NotImplemented();
  }
  } else {
    result->NotImplemented();
  }
}

}  // namespace multi_platform_bluetooth_printer
