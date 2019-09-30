/*
 * Project BLELightReader
 * Description: A simple light measurement hardware project that broadcasts the values over BLE.
 * Author: Andres Lopez (andres@bolted.io)
 * Date: 2019-09
 */
SYSTEM_MODE(MANUAL);

const int PHOTOSENSOR_PIN = A0;

const unsigned long UPDATE_PERIOD_MS = 100;
unsigned long lastUpdate = 0;

const BleUuid SERVICE_UUID("4677062c-ad02-4034-9abf-98581772427c");
const BleUuid PHOTOSENSOR_UUID("dc13b36a-3499-46b0-ac11-5ac0173c4cc5");

BleCharacteristic photosensorCharacteristic("photosensor", BleCharacteristicProperty::NOTIFY, PHOTOSENSOR_UUID, SERVICE_UUID);

// setup() runs once, when the device is first turned on.
void setup() {
  Serial.begin();

  BLE.addCharacteristic(photosensorCharacteristic);

  BleAdvertisingData data;
  data.appendServiceUUID(SERVICE_UUID);
  BLE.advertise(&data);
}

// loop() runs over and over again, as quickly as it can execute.
void loop() {
  if (BLE.connected())
  {
    if (millis() - lastUpdate >= UPDATE_PERIOD_MS)
    {
      lastUpdate = millis();

      int32_t data;
      data = analogRead(PHOTOSENSOR_PIN);

      Serial.printlnf("%d", data);

      photosensorCharacteristic.setValue(data);
    }
  }
}