import 'package:plugin_platform_interface/plugin_platform_interface.dart';

import 'multi_platform_bluetooth_printer_method_channel.dart';

abstract class MultiPlatformBluetoothPrinterPlatform extends PlatformInterface {
  /// Constructs a MultiPlatformBluetoothPrinterPlatform.
  MultiPlatformBluetoothPrinterPlatform() : super(token: _token);

  static final Object _token = Object();

  static MultiPlatformBluetoothPrinterPlatform _instance = MethodChannelMultiPlatformBluetoothPrinter();

  /// The default instance of [MultiPlatformBluetoothPrinterPlatform] to use.
  ///
  /// Defaults to [MethodChannelMultiPlatformBluetoothPrinter].
  static MultiPlatformBluetoothPrinterPlatform get instance => _instance;

  /// Platform-specific implementations should set this with their own
  /// platform-specific class that extends [MultiPlatformBluetoothPrinterPlatform] when
  /// they register themselves.
  static set instance(MultiPlatformBluetoothPrinterPlatform instance) {
    PlatformInterface.verifyToken(instance, _token);
    _instance = instance;
  }

  Future<String?> getPlatformVersion() {
    throw UnimplementedError('platformVersion() has not been implemented.');
  }
}
