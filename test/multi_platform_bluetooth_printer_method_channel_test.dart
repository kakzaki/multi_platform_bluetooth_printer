import 'package:flutter/services.dart';
import 'package:flutter_test/flutter_test.dart';
import 'package:multi_platform_bluetooth_printer/multi_platform_bluetooth_printer_method_channel.dart';

void main() {
  TestWidgetsFlutterBinding.ensureInitialized();

  MethodChannelMultiPlatformBluetoothPrinter platform = MethodChannelMultiPlatformBluetoothPrinter();
  const MethodChannel channel = MethodChannel('multi_platform_bluetooth_printer');

  setUp(() {
    TestDefaultBinaryMessengerBinding.instance.defaultBinaryMessenger.setMockMethodCallHandler(
      channel,
      (MethodCall methodCall) async {
        return '42';
      },
    );
  });

  tearDown(() {
    TestDefaultBinaryMessengerBinding.instance.defaultBinaryMessenger.setMockMethodCallHandler(channel, null);
  });

  test('getPlatformVersion', () async {
    expect(await platform.getPlatformVersion(), '42');
  });
}
