package dev.kakzaki.multi_platform_bluetooth_printer

import android.bluetooth.BluetoothAdapter
import android.bluetooth.le.ScanCallback
import android.bluetooth.le.ScanResult
import android.content.Context
import android.util.Log
import io.flutter.BuildConfig
import io.flutter.embedding.engine.plugins.FlutterPlugin
import io.flutter.plugin.common.EventChannel
import io.flutter.plugin.common.MethodCall
import io.flutter.plugin.common.MethodChannel
import io.flutter.plugin.common.MethodChannel.MethodCallHandler
import io.flutter.plugin.common.MethodChannel.Result
import java.nio.ByteBuffer

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
  private var scanChannel: EventChannel? = null
  private lateinit var scanSink: EventChannel.EventSink
  private val mDevices = mutableListOf<Any>()

  override fun onAttachedToEngine(flutterPluginBinding: FlutterPlugin.FlutterPluginBinding) {
    channel = MethodChannel(flutterPluginBinding.binaryMessenger, "multi_platform_bluetooth_printer")
    channel.setMethodCallHandler(this)
    mContext = flutterPluginBinding.applicationContext;
    bluetoothAdapter = BluetoothAdapter.getDefaultAdapter()
    ble = BlePlugin(mContext)
    scanChannel = EventChannel(flutterPluginBinding.binaryMessenger, "onScan")
    scanChannel!!.setStreamHandler(scanResultsHandler)
  }

  override fun onMethodCall(call: MethodCall, result: Result) {
    when(call.method){
      "startScanning" -> ble.startScanning(scanCallback)
      "stopScanning" -> ble.stopScanning(scanCallback)
      "connect" -> {
        ble.connect("Address")
      }
      "disconnect" -> ble.disconnect()
      "writeData" -> {
        val dataBytes: ByteArray? = call.argument<ByteArray?>("dataBytes")
        ble.writeData(dataBytes!!)
      }
    }
  }

  override fun onDetachedFromEngine(binding: FlutterPlugin.FlutterPluginBinding) {
    channel.setMethodCallHandler(null)
  }

  private val scanCallback = object : ScanCallback() {

    override fun onScanResult(callbackType: Int, result: ScanResult) {
      if (BuildConfig.DEBUG) {
        Log.d("ScanResult", "$result")
      }
      var device = result.device;
      val item: MutableMap<String, Any> = HashMap()
      item["deviceName"] = device.name
      item["deviceMacAddress"] = device.address

      if (!(mDevices.contains(item))) {
        mDevices.add(item)
      }
      scanSink.success(mDevices)
    }
  }

  private val scanResultsHandler: EventChannel.StreamHandler =
    object : EventChannel.StreamHandler {
      override fun onListen(o: Any?, eventSink: EventChannel.EventSink?) {
        if (eventSink != null) {
          scanSink = eventSink
        }
      }

      override fun onCancel(o: Any?) {
      }
    }

}
