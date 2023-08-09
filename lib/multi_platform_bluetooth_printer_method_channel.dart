import 'package:flutter/foundation.dart';
import 'package:flutter/services.dart';

import 'multi_platform_bluetooth_printer_platform_interface.dart';

/// An implementation of [MultiPlatformBluetoothPrinterPlatform] that uses method channels.
class MethodChannelMultiPlatformBluetoothPrinter extends MultiPlatformBluetoothPrinterPlatform {
  /// The method channel used to interact with the native platform.
  @visibleForTesting
  final methodChannel = const MethodChannel('multi_platform_bluetooth_printer');

  @override
  Future<String?> getPlatformVersion() async {
    final version = await methodChannel.invokeMethod<String>('getPlatformVersion');
    return version;
  }
}
