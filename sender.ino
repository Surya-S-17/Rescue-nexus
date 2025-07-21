#include <esp_now.h>
#include <WiFi.h>
#include <esp_wifi.h>  // Add this to use esp_wifi_set_channel

// 📡 Broadcast MAC address
uint8_t broadcastAddress[] = {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF};

void setup() {
  Serial.begin(115200);
  WiFi.begin();
  WiFi.mode(WIFI_STA);

  WiFi.setTxPower(WIFI_POWER_MINUS_1dBm);  // ✅ Set TX power to -1 dBm (~1 meter range)


  esp_wifi_set_channel(1, WIFI_SECOND_CHAN_NONE);  // ✅ Set the channel to match the receiver

  if (esp_now_init() != ESP_OK) {
    Serial.println("❌ ESP-NOW Init Failed");
    return;
  }

  // 👥 Add peer
  esp_now_peer_info_t peerInfo = {};
  memcpy(peerInfo.peer_addr, broadcastAddress, 6);
  peerInfo.channel = 1;
  peerInfo.encrypt = false;

  if (esp_now_add_peer(&peerInfo) != ESP_OK) {
    Serial.println("❌ Failed to add peer");
    return;
  }

  delay(2000); // ⏳ Give receivers time to initialize

  const char *msg = "alert!";

  // 📤 Send twice
  esp_now_send(broadcastAddress, (uint8_t *)msg, strlen(msg));
  delay(100);
  esp_now_send(broadcastAddress, (uint8_t *)msg, strlen(msg));
  Serial.println("✅ Message broadcasted!");
}

void loop() {
  // 🔁 Optional repeat logic
}
