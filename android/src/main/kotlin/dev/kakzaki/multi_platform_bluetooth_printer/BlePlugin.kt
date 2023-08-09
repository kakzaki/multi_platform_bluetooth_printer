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

  // Callback for GATT client connection state changes
  private val gattCallback = object : BluetoothGattCallback() {

    // Handle connected and disconnected state
    override fun onConnectionStateChange(gatt: BluetoothGatt, status: Int, newState: Int) {
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
  fun connect(device: BluetoothDevice) {
    device.connectGatt(context, false, gattCallback)
  }

  // Disconnect GATT client
  fun disconnect(gatt: BluetoothGatt) {
    gatt.disconnect()
  }

  // Write data to characteristic
  fun writeData(gatt: BluetoothGatt, serviceUuid: UUID, charUuid: UUID, data: ByteArray) {

    val service = gatt.getService(serviceUuid)
    val characteristic = service.getCharacteristic(charUuid)

    if (android.os.Build.VERSION.SDK_INT >= android.os.Build.VERSION_CODES.TIRAMISU) {
      // Set the value of the characteristic to the data
      gatt.writeCharacteristic(characteristic,data,BluetoothGattCharacteristic.WRITE_TYPE_DEFAULT)
    } else {

      characteristic.writeType = BluetoothGattCharacteristic.WRITE_TYPE_DEFAULT
      // Set the value of the characteristic to the data
      characteristic.value=data
      gatt.writeCharacteristic(characteristic)
    }

  }

}