#include <Wire.h>
#include <WiFi.h>
#include <esp_now.h>

// ================== Pins ==================
#define SDA_PIN 21
#define SCL_PIN 22

// ================== MPU6050 ==================
#define MPU_ADDR 0x68

// ================== Thresholds ==================
const float p_threshold = 0.05;
const float s_threshold = 0.12;
const float major_threshold = 0.30;

// ================== Wave State ==================
enum WaveState { NONE, P_WAVE, S_WAVE, MAJOR };
WaveState currentWave = NONE;

// ================== ESP-NOW Peer ==================
uint8_t peerAddress[] = {0xB0, 0xA7, 0x32, 0x2D, 0x91, 0x88};   // Replace with peer MAC

// ================== Message Struct ==================
typedef struct struct_message {
  float deviation;
  uint8_t waveType;   // 0=NONE,1=P,2=S,3=MAJOR
  bool quake;
} struct_message;

struct_message msg;
struct_message incomingMsg;

// ================== Flags ==================
bool localQuake = false;
bool remoteQuake = false;
String remoteType = "";

// ================== ESP-NOW Callbacks ==================

// Send callback
void OnDataSent(const uint8_t *mac_addr, esp_now_send_status_t status) {
  if (status == ESP_NOW_SEND_SUCCESS) {
    Serial.println("✅ ESP-NOW send success");
  } else {
    Serial.println("❌ ESP-NOW send fail");
  }
}

// Receive callback (new ESP32 core requires esp_now_recv_info)
void OnDataRecv(const esp_now_recv_info *info, const uint8_t *incomingData, int len) {
  if (len == sizeof(incomingMsg)) {
    memcpy(&incomingMsg, incomingData, sizeof(incomingMsg));
    remoteQuake = incomingMsg.quake;

    switch (incomingMsg.waveType) {
      case 1: remoteType = "P-wave"; break;
      case 2: remoteType = "S-wave"; break;
      case 3: remoteType = "MAJOR"; break;
      default: remoteType = "None"; break;
    }

    char macStr[18];
    snprintf(macStr, sizeof(macStr), "%02X:%02X:%02X:%02X:%02X:%02X",
             info->src_addr[0], info->src_addr[1], info->src_addr[2],
             info->src_addr[3], info->src_addr[4], info->src_addr[5]);

    Serial.printf("📩 Data received from %s | Quake=%d, Wave=%s\n",
                  macStr, remoteQuake, remoteType.c_str());
  }
}

// ================== Setup ==================
void setup() {
  Serial.begin(115200);
  Wire.begin(SDA_PIN, SCL_PIN);

  // Wake up MPU6050
  Wire.beginTransmission(MPU_ADDR);
  Wire.write(0x6B);
  Wire.write(0);
  Wire.endTransmission(true);

  WiFi.mode(WIFI_STA);
  if (esp_now_init() != ESP_OK) {
    Serial.println("ESP-NOW init failed!");
    return;
  }

  esp_now_register_send_cb(OnDataSent);
  esp_now_register_recv_cb(OnDataRecv);

  esp_now_peer_info_t peerInfo = {};
  memcpy(peerInfo.peer_addr, peerAddress, 6);
  peerInfo.channel = 0;
  peerInfo.encrypt = false;
  if (esp_now_add_peer(&peerInfo) != ESP_OK) {
    Serial.println("❌ Failed to add peer");
  } else {
    Serial.println("✅ Peer added successfully");
  }

  Serial.println("System ready!");
}

// ================== Read MPU6050 ==================
bool readMPU6050(float &ax, float &ay, float &az) {
  int16_t AcX, AcY, AcZ;
  Wire.beginTransmission(MPU_ADDR);
  Wire.write(0x3B);
  if (Wire.endTransmission(false) != 0) return false;
  if (Wire.requestFrom(MPU_ADDR, 6, true) != 6) return false;
  AcX = Wire.read() << 8 | Wire.read();
  AcY = Wire.read() << 8 | Wire.read();
  AcZ = Wire.read() << 8 | Wire.read();
  ax = AcX / 16384.0f;
  ay = AcY / 16384.0f;
  az = AcZ / 16384.0f;
  return true;
}

// ================== Loop ==================
void loop() {
  float ax, ay, az;
  if (!readMPU6050(ax, ay, az)) {
    Serial.println("⚠️ Failed to read MPU6050");
    delay(500);
    return;
  }

  float mag = sqrt(ax * ax + ay * ay + az * az);
  float dev = fabs(mag - 1.0);

  uint8_t waveType = 0;
  localQuake = false;

  if (dev >= major_threshold) {
    waveType = 3;
    localQuake = true;
    Serial.println("⚡ Major wave detected!");
  } else if (dev >= s_threshold) {
    waveType = 2;
    localQuake = true;
    Serial.println("⚠️ S-wave detected!");
  } else if (dev >= p_threshold) {
    waveType = 1;
    localQuake = true;
    Serial.println("ℹ️ P-wave detected!");
  }

  // Prepare message
  msg.deviation = dev;
  msg.waveType = waveType;
  msg.quake = localQuake;

  // Send to peer
  esp_now_send(peerAddress, (uint8_t *)&msg, sizeof(msg));

  // Check both systems
  if (localQuake && remoteQuake) {
    Serial.println("🚨 TRUE EARTHQUAKE ALERT (Both systems agree!)");
  } else if (localQuake || remoteQuake) {
    Serial.println("❌ False Alarm (Only one system detected)");
  }

  // Show MPU values
  Serial.printf("[MPU] Ax=%.2f Ay=%.2f Az=%.2f | Dev=%.3f\n", ax, ay, az, dev);

  delay(1000);
}
