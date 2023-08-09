//
//  Generated file. Do not edit.
//

// clang-format off

#include "generated_plugin_registrant.h"

#include <multi_platform_bluetooth_printer/multi_platform_bluetooth_printer_plugin.h>

void fl_register_plugins(FlPluginRegistry* registry) {
  g_autoptr(FlPluginRegistrar) multi_platform_bluetooth_printer_registrar =
      fl_plugin_registry_get_registrar_for_plugin(registry, "MultiPlatformBluetoothPrinterPlugin");
  multi_platform_bluetooth_printer_plugin_register_with_registrar(multi_platform_bluetooth_printer_registrar);
}
