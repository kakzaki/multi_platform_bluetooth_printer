#include <glib.h>
#include <gio/gio.h>
#include <functional>

class BlePlugin {

public:

  BlePlugin(GDBusConnection* connection) {
    this->connection = connection;

    // Initialize GIO Bluetooth classes
    init_bluez();
  }

  ~BlePlugin() {
    g_object_unref(adapter_proxy);
  }

  void startScanning(std::function<void(const gchar*)> callback) {
    // Start discovery
    g_dbus_proxy_call(adapter_proxy, "StartDiscovery", nullptr, G_DBUS_CALL_FLAGS_NONE, -1, nullptr, nullptr);

    // Connect to DeviceFound signal
    scan_callback = callback;
    g_signal_connect(adapter_proxy, "DeviceFound", G_CALLBACK(on_device_found), this);
  }

  void stopScanning() {
    // Stop discovery
    g_dbus_proxy_call(adapter_proxy, "StopDiscovery", nullptr, G_DBUS_CALL_FLAGS_NONE, -1, nullptr, nullptr);

    g_signal_handlers_disconnect_by_func(adapter_proxy, on_device_found, this);
    scan_callback = nullptr;
  }

  void connect(const std::string& address) {
    // Connect to device
  }

  void disconnect() {
    // Disconnect
  }

  void writeData(const uint8_t* data, size_t length) {
    // Write data
  }

private:

  GDBusConnection* connection;
  GDBusProxy* adapter_proxy;
  std::function<void(const gchar*)> scan_callback;

  void init_bluez() {
    // Get adapter proxy
  }

  static void on_device_found(GDBusProxy* proxy, const gchar* sender_name, const gchar* signal_name, GVariant* parameters, gpointer user_data) {
    // Get device address
    const gchar* address = g_variant_get_string(parameters, nullptr);

    // Call callback
    auto* plugin = static_cast<BlePlugin*>(user_data); 
    plugin->scan_callback(address);
  }

};