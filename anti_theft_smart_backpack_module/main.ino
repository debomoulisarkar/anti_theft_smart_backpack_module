#include <BLEDevice.h>
#include <BLEServer.h>
#include <Wire.h>
#include <MPU6050.h>

MPU6050 mpu;

int buzzerPin = 25;

bool deviceConnected = false;
bool bagMoved = false;

BLEServer *pServer;

// BLE callbacks
class MyServerCallbacks: public BLEServerCallbacks {

  void onConnect(BLEServer* pServer) {
    deviceConnected = true;
    Serial.println("Phone CONNECTED to backpack");
  }

  void onDisconnect(BLEServer* pServer) {
    deviceConnected = false;
    Serial.println("Phone DISCONNECTED");

    pServer->getAdvertising()->start();
    Serial.println("Advertising restarted");
  }

};

void setup() {

  Serial.begin(115200);

  pinMode(buzzerPin, OUTPUT);
  digitalWrite(buzzerPin, LOW);

  BLEDevice::init("SmartBackpack");

  pServer = BLEDevice::createServer();
  pServer->setCallbacks(new MyServerCallbacks());

  BLEService *pService = pServer->createService("4fafc201-1fb5-459e-8fcc-c5c9c331914b");

  BLECharacteristic *pCharacteristic =
    pService->createCharacteristic(
      "beb5483e-36e1-4688-b7f5-ea07361b26a8",
      BLECharacteristic::PROPERTY_READ |
      BLECharacteristic::PROPERTY_WRITE
    );

  pCharacteristic->setValue("Backpack System");

  pService->start();
  BLEDevice::getAdvertising()->start();

  Serial.println("BLE Advertising Started");

  Wire.begin(21,22);

  Serial.println("Initializing MPU6050...");

  mpu.initialize();

  if (mpu.testConnection()) {
    Serial.println("MPU6050 connected successfully");
  } else {
    Serial.println("MPU6050 connection FAILED");
  }

}

void loop() {

  int16_t ax, ay, az;
  int16_t gx, gy, gz;

  mpu.getMotion6(&ax,&ay,&az,&gx,&gy,&gz);

  int motion = abs(ax) + abs(ay) + abs(az);

  Serial.print("Motion Value: ");
  Serial.println(motion);

  // LOWER threshold
  if(motion > 22000)
    bagMoved = true;
  else
    bagMoved = false;

  // SYSTEM STATUS
  if(deviceConnected && !bagMoved)
  {
    Serial.println("STATUS: SAFE (phone connected, bag still)");
    digitalWrite(buzzerPin, LOW);
  }

  if(deviceConnected && bagMoved)
  {
    Serial.println("STATUS: SAFE (bag moved but phone connected)");
    digitalWrite(buzzerPin, LOW);
  }

  if(!deviceConnected && !bagMoved)
  {
    Serial.println("STATUS: SAFE (phone away but bag still)");
    digitalWrite(buzzerPin, LOW);
  }

  if(!deviceConnected && bagMoved)
  {
    Serial.println("STATUS: THEFT DETECTED");
    digitalWrite(buzzerPin, HIGH);
  }

  Serial.println("----------------------");

  delay(500);
}