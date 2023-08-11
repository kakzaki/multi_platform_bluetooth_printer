import CoreBluetooth

class BlePlugin: NSObject, CBCentralManagerDelegate, CBPeripheralDelegate {

  var centralManager: CBCentralManager!
  var peripheral: CBPeripheral!
  var serviceUUID: CBUUID!
  var charUUID: CBUUID!

  override init() {
    super.init()
    centralManager = CBCentralManager(delegate: self, queue: nil)
  }

  // Start and stop scanning
  func startScanning(_ scanCallback: @escaping ([CBPeripheral]) -> Void) {
    centralManager.scanForPeripherals(withServices: nil, options: nil)
  }

  func stopScanning() {
    centralManager.stopScan()
  }

  // Connect to device
  func connect(_ peripheral: CBPeripheral) {
    self.peripheral = peripheral
    peripheral.delegate = self
    centralManager.connect(peripheral, options: nil)
  }

  // Handle connected and disconnected state
  func centralManager(_ central: CBCentralManager, didConnect peripheral: CBPeripheral) {
    peripheral.discoverServices([CBUUID(string: "service_uuid")])
  }

  func centralManager(_ central: CBCentralManager, didDisconnectPeripheral peripheral: CBPeripheral, error: Error?) {
    // Disconnected
  }

  // Get service and characteristic UUIDs
  func peripheral(_ peripheral: CBPeripheral, didDiscoverServices error: Error?) {
    guard let services = peripheral.services else { return }

    for service in services {
      self.serviceUUID = service.uuid

      for characteristic in service.characteristics! {
        self.charUUID = characteristic.uuid
      }
    }
  }

  // Write data to characteristic
  func writeData(_ data: Data) {
    guard let characteristic = peripheral.services?.first?.characteristics?.first else { return }

    peripheral.writeValue(data, for: characteristic, type: .withoutResponse)
  }

}