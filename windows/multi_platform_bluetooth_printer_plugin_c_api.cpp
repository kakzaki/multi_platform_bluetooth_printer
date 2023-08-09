#include "include/multi_platform_bluetooth_printer/multi_platform_bluetooth_printer_plugin_c_api.h"

#include <flutter/plugin_registrar_windows.h>

#include "multi_platform_bluetooth_printer_plugin.h"

void MultiPlatformBluetoothPrinterPluginCApiRegisterWithRegistrar(
    FlutterDesktopPluginRegistrarRef registrar) {
  multi_platform_bluetooth_printer::MultiPlatformBluetoothPrinterPlugin::RegisterWithRegistrar(
      flutter::PluginRegistrarManager::GetInstance()
          ->GetRegistrar<flutter::PluginRegistrarWindows>(registrar));
}
