import 'package:flutter_test/flutter_test.dart';
import 'package:multi_platform_bluetooth_printer/multi_platform_bluetooth_printer.dart';
import 'package:multi_platform_bluetooth_printer/multi_platform_bluetooth_printer_platform_interface.dart';
import 'package:multi_platform_bluetooth_printer/multi_platform_bluetooth_printer_method_channel.dart';
import 'package:plugin_platform_interface/plugin_platform_interface.dart';

class MockMultiPlatformBluetoothPrinterPlatform
    with MockPlatformInterfaceMixin
    implements MultiPlatformBluetoothPrinterPlatform {

  @override
  Future<String?> getPlatformVersion() => Future.value('42');
}

void main() {
  final MultiPlatformBluetoothPrinterPlatform initialPlatform = MultiPlatformBluetoothPrinterPlatform.instance;

  test('$MethodChannelMultiPlatformBluetoothPrinter is the default instance', () {
    expect(initialPlatform, isInstanceOf<MethodChannelMultiPlatformBluetoothPrinter>());
  });

  test('getPlatformVersion', () async {
    MultiPlatformBluetoothPrinter multiPlatformBluetoothPrinterPlugin = MultiPlatformBluetoothPrinter();
    MockMultiPlatformBluetoothPrinterPlatform fakePlatform = MockMultiPlatformBluetoothPrinterPlatform();
    MultiPlatformBluetoothPrinterPlatform.instance = fakePlatform;

    expect(await multiPlatformBluetoothPrinterPlugin.getPlatformVersion(), '42');
  });
}
