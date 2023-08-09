
import 'multi_platform_bluetooth_printer_platform_interface.dart';

class MultiPlatformBluetoothPrinter {
  Future<String?> getPlatformVersion() {
    return MultiPlatformBluetoothPrinterPlatform.instance.getPlatformVersion();
  }
}
