#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <esp_now.h>
#include <WiFi.h>
#include <esp_wifi.h>
#include <MPU6050_light.h>
#include <math.h> // For sqrt()

// 📟 OLED setup
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

// 📈 MPU6050 setup
MPU6050 mpu(Wire);
unsigned long timer = 0;

// 🔔 Buzzer pin
#define BUZZER_PIN 14

// 📡 Broadcast Address
uint8_t broadcastAddress[] = {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF};

// 📥 On Data Received Callback
void OnDataRecv(const esp_now_recv_info_t *info, const uint8_t *incomingData, int len) {
  String receivedMsg = "";

  for (int i = 0; i < len; i++) {
    receivedMsg += (char)incomingData[i];
  }

  Serial.print("📥 Received: ");
  Serial.println(receivedMsg);

  // 🖥 Display on OLED
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0, 0);
  display.println("Received Msg:");
  display.setCursor(0, 20);
  display.println(receivedMsg.substring(0, 20)); // Show first 20 chars
  display.display();

  // 🔔 Buzz for 3 seconds
  digitalWrite(BUZZER_PIN, HIGH);
  delay(3000);
  digitalWrite(BUZZER_PIN, LOW);

  // 🔁 Forward to others
  esp_err_t result = esp_now_send(broadcastAddress, (uint8_t *)receivedMsg.c_str(), receivedMsg.length());

  if (result == ESP_OK) {
    Serial.println("📤 Forwarded successfully");
  } else {
    Serial.println("⚠ Forward failed");
  }
}

void setup() {
  Serial.begin(115200);

  // ✅ Buzzer setup
  pinMode(BUZZER_PIN, OUTPUT);
  digitalWrite(BUZZER_PIN, LOW);

  // ✅ OLED setup
  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println("❌ OLED init failed");
    while (true);
  }
  display.clearDisplay();
  display.setTextSize(3);
  display.setTextColor(WHITE);
  display.setCursor(0, 0);
  display.println("Receiver Ready");
  display.display();

  // ✅ WiFi setup
  WiFi.begin();
  WiFi.mode(WIFI_STA);
  esp_wifi_set_channel(1, WIFI_SECOND_CHAN_NONE); // Match channel

  if (esp_now_init() != ESP_OK) {
    Serial.println("❌ ESP-NOW Init Failed");
    display.setCursor(0, 20);
    display.println("ESP-NOW FAIL");
    display.display();
    return;
  }

  esp_now_register_recv_cb(OnDataRecv);

  // 📡 Add broadcast peer
  esp_now_peer_info_t peerInfo = {};
  memcpy(peerInfo.peer_addr, broadcastAddress, 6);
  peerInfo.channel = 1;
  peerInfo.encrypt = false;
  esp_now_add_peer(&peerInfo);

  Serial.println("✅ ESP-NOW Ready");

  // ✅ MPU6050 setup
  Wire.begin(21, 22); // SDA=21, SCL=22 for ESP32
  byte status = mpu.begin();
  if (status != 0) {
    Serial.print("❌ MPU6050 Init Failed with code: ");
    Serial.println(status);
    while (1);
  }
  Serial.println("✅ MPU6050 ready");
  delay(1000);
  mpu.calcOffsets(); // Calibrate sensor
  Serial.println("✅ Calibration Done");
}

void loop() {
  mpu.update();

  if (millis() - timer > 200) {
    timer = millis();

    // Read Accel & Gyro
    float accX = mpu.getAccX();
    float accY = mpu.getAccY();
    float accZ = mpu.getAccZ();

    float gyroX = mpu.getGyroX();
    float gyroY = mpu.getGyroY();
    float gyroZ = mpu.getGyroZ();

    // Calculate magnitude
    float accMag = sqrt(pow(accX, 2) + pow(accY, 2) + pow(accZ, 2));
    float gyroMag = sqrt(pow(gyroX, 2) + pow(gyroY, 2) + pow(gyroZ, 2));
    float totalMag = accMag + gyroMag;

    float accidentThreshold = 300.0; // 🚑

    if (totalMag > accidentThreshold) {
      Serial.println("🚨 Accident Detected");

      // 🖥 Display on OLED
      display.clearDisplay();
      display.setTextSize(1);
      display.setTextColor(WHITE);
      display.setCursor(0, 0);
      display.println("🚨 Accident!");
      display.display();

      // 🔔 Buzz
      digitalWrite(BUZZER_PIN, HIGH);
      delay(3000);
      digitalWrite(BUZZER_PIN, LOW);

      // 📤 Send "ACCIDENT" message
      String accidentMsg = "ACCIDENT DETECTED";
      esp_now_send(broadcastAddress, (uint8_t *)accidentMsg.c_str(), accidentMsg.length());
    }
  }
}
