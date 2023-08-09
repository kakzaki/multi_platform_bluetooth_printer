package dev.kakzaki.multi_platform_bluetooth_printer

import android.bluetooth.*
import android.bluetooth.le.ScanCallback
import android.content.Context
import java.util.UUID

// BlePlugin class to handle BLE operations
class BlePlugin(private val context: Context) {

  // Get BluetoothAdapter instance using BluetoothManager
  private val bluetoothManager = context.getSystemService(Context.BLUETOOTH_SERVICE) as BluetoothManager
  private val bluetoothAdapter = bluetoothManager.adapter
  private lateinit var bluetoothGatt : BluetoothGatt
  private lateinit var serviceUuid : UUID
  private lateinit var charUuid : UUID

  // Callback for GATT client connection state changes
  private val gattCallback = object : BluetoothGattCallback() {

    override fun onServicesDiscovered(gatt: BluetoothGatt, status: Int) {

      // Get first service
      val service = gatt.services[0]

      serviceUuid = service.uuid

      // Get first characteristic
      val characteristic = service.characteristics[0]

      charUuid = characteristic.uuid

    }

    // Handle connected and disconnected state
    override fun onConnectionStateChange(gatt: BluetoothGatt, status: Int, newState: Int) {
      bluetoothGatt = gatt
      when (newState) {
        BluetoothProfile.STATE_CONNECTED -> {
          // Successfully connected
        }

        BluetoothProfile.STATE_DISCONNECTED -> {
          // Disconnected, close gatt client
          gatt.close()
        }
      }
    }

    // Handle characteristic write result
    override fun onCharacteristicWrite(gatt: BluetoothGatt, characteristic: BluetoothGattCharacteristic, status: Int) {
      bluetoothGatt = gatt
      when (status) {
        BluetoothGatt.GATT_SUCCESS -> {
          // Characteristic was written successfully
        }
        else -> {
          // Write failed with error code 'status'
        }
      }
    }

  }

  // Start and stop scanning
  fun startScanning(scanCallback: ScanCallback) {
    bluetoothAdapter.bluetoothLeScanner.startScan(scanCallback)
  }

  fun stopScanning(scanCallback: ScanCallback) {
    bluetoothAdapter.bluetoothLeScanner.stopScan(scanCallback)
  }

  // Connect to device

  fun connect(address: String) {
    val device = bluetoothAdapter.getRemoteDevice(address)
    device.connectGatt(context, false, gattCallback)
  }

  // Disconnect GATT client
  fun disconnect() {
    bluetoothGatt.disconnect()
  }

  // Write data to characteristic
  fun writeData(data: ByteArray) {
    val service = bluetoothGatt.getService(serviceUuid)
    val characteristic = service.getCharacteristic(charUuid)

    if (android.os.Build.VERSION.SDK_INT >= android.os.Build.VERSION_CODES.TIRAMISU) {
      // Set the value of the characteristic to the data
      bluetoothGatt.writeCharacteristic(characteristic,data,BluetoothGattCharacteristic.WRITE_TYPE_DEFAULT)
    } else {

      characteristic.writeType = BluetoothGattCharacteristic.WRITE_TYPE_DEFAULT
      // Set the value of the characteristic to the data
      characteristic.value=data
      bluetoothGatt.writeCharacteristic(characteristic)
    }

  }

}