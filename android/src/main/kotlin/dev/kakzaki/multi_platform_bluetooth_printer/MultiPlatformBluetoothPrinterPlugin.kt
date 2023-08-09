package dev.kakzaki.multi_platform_bluetooth_printer

import android.bluetooth.BluetoothAdapter
import android.bluetooth.BluetoothDevice
import android.bluetooth.le.ScanCallback
import android.bluetooth.le.ScanResult
import android.content.Context
import android.util.Log
import io.flutter.embedding.engine.plugins.FlutterPlugin
import io.flutter.plugin.common.MethodCall
import io.flutter.plugin.common.MethodChannel
import io.flutter.plugin.common.MethodChannel.MethodCallHandler
import io.flutter.plugin.common.MethodChannel.Result

/** MultiPlatformBluetoothPrinterPlugin */
class MultiPlatformBluetoothPrinterPlugin: FlutterPlugin, MethodCallHandler {
  /// The MethodChannel that will the communication between Flutter and native Android
  ///
  /// This local reference serves to register the plugin with the Flutter Engine and unregister it
  /// when the Flutter Engine is detached from the Activity
  private lateinit var channel : MethodChannel
  private lateinit var ble : BlePlugin
  private lateinit var bluetoothAdapter: BluetoothAdapter
  private lateinit var mContext: Context

  override fun onAttachedToEngine(flutterPluginBinding: FlutterPlugin.FlutterPluginBinding) {
    channel = MethodChannel(flutterPluginBinding.binaryMessenger, "multi_platform_bluetooth_printer")
    channel.setMethodCallHandler(this)
    mContext = flutterPluginBinding.applicationContext;
    bluetoothAdapter = BluetoothAdapter.getDefaultAdapter()
    ble = BlePlugin(mContext)
  }

  override fun onMethodCall(call: MethodCall, result: Result) {
    when(call.method){
      "startScanning" -> ble.startScanning(scanCallback)
      "stopScanning" -> ble.stopScanning(scanCallback)
      "connect" -> {
        ble.connect("Address")
      }
      "disconnect" -> ble.disconnect()
      "writeData" -> ble.writeData()
    }
  }

  override fun onDetachedFromEngine(binding: FlutterPlugin.FlutterPluginBinding) {
    channel.setMethodCallHandler(null)
  }

  private val scanCallback = object : ScanCallback() {

    override fun onScanResult(callbackType: Int, result: ScanResult) {
      var deviceId = result.device.address;
      Log.d("ScanResult", "$result")
    }
  }

}
