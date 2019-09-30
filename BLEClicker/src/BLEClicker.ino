/*
 * Project BLEClicker
 * Description: A Slide clicker over BLE
 * Author: Andres Lopez (andres@bolted.io)
 * Date: 2019-09-18
 */
SYSTEM_MODE(MANUAL);

// Clicker key map
const uint8_t ARROW_LEFT = 37;
const uint8_t ARROW_RIGHT = 39;
const uint8_t NOOP = 0;

// Pins
const int leftKeyPin = D11;
const int rightKeyPin = D3;

///// BLE
// HID Service
const BleUuid serviceUuid("4677062c-ad02-4034-9abf-98581772427c");
const BleUuid valueUuid("dc13b36a-3499-46b0-ac11-5ac0173c4cc5");

BleCharacteristic valueCharacteristic("value", BleCharacteristicProperty::NOTIFY, valueUuid, serviceUuid);

// Device Information Service
BleUuid infoService(BLE_SIG_UUID_DEVICE_INFORMATION_SVC);
BleCharacteristic makeCharacteristic("make", BleCharacteristicProperty::READ, BleUuid(0x2A29), infoService);

// Scan Parameters Profile

void setup()
{
  // INIT Pins
  pinMode(leftKeyPin, INPUT_PULLDOWN);
  pinMode(rightKeyPin, INPUT_PULLDOWN);

  /// INIT BLE
  BLE.addCharacteristic(valueCharacteristic);

  BleAdvertisingData data;
  data.appendServiceUUID(serviceUuid);
  BLE.advertise(&data);
}

void loop()
{
  if (digitalRead(leftKeyPin) == HIGH)
  {
    valueCharacteristic.setValue(ARROW_LEFT);
  }
  else if (digitalRead(rightKeyPin) == HIGH)
  {
    valueCharacteristic.setValue(ARROW_RIGHT);
  }
  else
  {
    valueCharacteristic.setValue(NOOP);
  }
}