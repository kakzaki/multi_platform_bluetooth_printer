#include "include/multi_platform_bluetooth_printer/multi_platform_bluetooth_printer_plugin.h"

#include <flutter_linux/flutter_linux.h>
#include <gtk/gtk.h>
#include <sys/utsname.h>

#include <cstring>

#include "multi_platform_bluetooth_printer_plugin_private.h"

#include "BlePlugin.h"

#define MULTI_PLATFORM_BLUETOOTH_PRINTER_PLUGIN(obj) \
  (G_TYPE_CHECK_INSTANCE_CAST((obj), multi_platform_bluetooth_printer_plugin_get_type(), \
                              MultiPlatformBluetoothPrinterPlugin))

struct _MultiPlatformBluetoothPrinterPlugin {
  GObject parent_instance;
};

G_DEFINE_TYPE(MultiPlatformBluetoothPrinterPlugin, multi_platform_bluetooth_printer_plugin, g_object_get_type())

// Called when a method call is received from Flutter.
static void multi_platform_bluetooth_printer_plugin_handle_method_call(
    MultiPlatformBluetoothPrinterPlugin* self,
    FlMethodCall* method_call) {
  g_autoptr(FlMethodResponse) response = nullptr;

 // Create BlePlugin instance
  blePlugin = new BlePlugin();

  const gchar* method = fl_method_call_get_name(method_call);

    if (strcmp(method, "startScan") == 0) {
      blePlugin->startScanning(scanCallback);

    } else if (strcmp(method, "stopScan") == 0) {
      blePlugin->stopScanning();

    } else if (strcmp(method, "connect") == 0) {
      // Get device address from method call arguments
      std::string address = GetArgument(method_call, "address");
      blePlugin->connect(address);

    } else if (strcmp(method, "write") == 0) {
      // Get data from method call arguments
      std::vector<uint8_t> data = GetArgument(method_call, "data");
      blePlugin->writeData(data.data(), data.size());

    } else {
        response = FL_METHOD_RESPONSE(fl_method_not_implemented_response_new());
      }
  fl_method_call_respond(method_call, response, nullptr);
}


static void multi_platform_bluetooth_printer_plugin_dispose(GObject* object) {
  G_OBJECT_CLASS(multi_platform_bluetooth_printer_plugin_parent_class)->dispose(object);
}

static void multi_platform_bluetooth_printer_plugin_class_init(MultiPlatformBluetoothPrinterPluginClass* klass) {
  G_OBJECT_CLASS(klass)->dispose = multi_platform_bluetooth_printer_plugin_dispose;
}

static void multi_platform_bluetooth_printer_plugin_init(MultiPlatformBluetoothPrinterPlugin* self) {}

static void method_call_cb(FlMethodChannel* channel, FlMethodCall* method_call,
                           gpointer user_data) {
  MultiPlatformBluetoothPrinterPlugin* plugin = MULTI_PLATFORM_BLUETOOTH_PRINTER_PLUGIN(user_data);
  multi_platform_bluetooth_printer_plugin_handle_method_call(plugin, method_call);
}

void multi_platform_bluetooth_printer_plugin_register_with_registrar(FlPluginRegistrar* registrar) {
  MultiPlatformBluetoothPrinterPlugin* plugin = MULTI_PLATFORM_BLUETOOTH_PRINTER_PLUGIN(
      g_object_new(multi_platform_bluetooth_printer_plugin_get_type(), nullptr));

  g_autoptr(FlStandardMethodCodec) codec = fl_standard_method_codec_new();
  g_autoptr(FlMethodChannel) channel =
      fl_method_channel_new(fl_plugin_registrar_get_messenger(registrar),
                            "multi_platform_bluetooth_printer",
                            FL_METHOD_CODEC(codec));
  fl_method_channel_set_method_call_handler(channel, method_call_cb,
                                            g_object_ref(plugin),
                                            g_object_unref);

  g_object_unref(plugin);
}
