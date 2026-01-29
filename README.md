# 🌍 Seismic Detection System

A real-time embedded system designed to detect seismic vibrations using two independent nodes that communicate and validate data collaboratively to generate a reliable earthquake alert.

---

## 🚨 Problem Statement
Earthquakes and tremors can cause serious damage and risk to human life. Most low-cost systems suffer from false alerts due to noise and lack of cross-validation.

---

## 🎯 Objective
To design a system that:
- 📡 Independently detects seismic waves using two embedded nodes  
- 🔁 Exchanges sensor data between nodes using MAC-based communication  
- 📊 Compares values with a predefined threshold  
- ⚠️ Classifies the event as either a false alert or a true earthquake  

---

## ✨ Features
- 🔍 Dual-node independent seismic detection  
- 🤝 Mutual data validation to reduce false positives  
- 🧮 Threshold-based decision algorithm  
- 🚨 Real-time alert generation  
- 📈 Reliable and scalable embedded design  

---

## 🔧 Hardware Components
- 🧠 ESP32-WROOM-32 Microcontroller (2 units)  
- 📐 ADXL345 / MPU6050 MEMS Accelerometer (2 units)  
- ⚡ Piezoelectric Vibration Sensor (SW-420) (2 units)  
- 🔔 Buzzer / LED Indicator  
- 🧵 Breadboard and Jumper Wires  
- 🔋 5V Power Supply / USB Power  

---

## 💻 Software & Tools
- 🛠️ Arduino IDE  
- 🧑‍💻 Embedded C  
- 🌐 ESP32 Wi-Fi / Bluetooth Stack  
- 🔗 MAC Address-based Peer-to-Peer Communication  

---

## ⚙️ How It Works

Both System 1 and System 2 continuously monitor ground vibrations using MEMS sensors.  
Each system processes its own sensor data locally and compares it with a predefined threshold.  
The processed data is then exchanged between the two systems using MAC-based wireless communication.  

If both systems confirm abnormal values beyond the threshold, the event is classified as a **✅ True Earthquake**.  
If only one system detects abnormal activity, it is classified as a **❌ False Alert**.

### Step-by-Step Flow
- System 1 continuously monitors ground vibrations using MEMS sensors  
- System 2 continuously monitors ground vibrations using MEMS sensors  

- Each system:
  - Processes its sensor data locally  
  - Compares readings with a predefined threshold  

- Both systems:
  - Exchange processed data using MAC-based wireless communication  
  - Perform cross-validation of sensor values  

- Decision Logic:
  - Both systems exceed threshold → ✅ True Earthquake  
  - Only one system exceeds threshold → ❌ False Alert  

- Final alert is generated using buzzer / LED indicators  

---

## 📏 Seismic Threshold Levels

The system uses acceleration-based thresholds (in *g-force*) to classify seismic activity:

### Wave Detection Thresholds
- P-wave threshold: ~ **0.05 g**  
- S-wave threshold: ~ **0.12 g**  
- Major earthquake: ≥ **0.30 g**

### Decision Classification
- < 0.05 g → Normal / No seismic activity  
- 0.05 g – 0.12 g → P-wave detected (initial tremor)  
- 0.12 g – 0.30 g → S-wave detected (moderate shaking)  
- ≥ 0.30 g → Major earthquake detected  

These thresholds are used by both systems before cross-validation.

---

## 🎯 System Accuracy

Based on experimental testing and calibration:
- Minor vibrations: **85–90%**  
- Moderate vibrations: **90–92%**  
- Strong vibrations: **96–98%**  
- Severe vibrations: **~98%**

Dual-node validation significantly improves reliability and reduces false positives.

---

## 🏥 Applications
- 🌏 Earthquake early warning systems  
- 🏥 Hospital and dialysis center safety  
- 🏗️ Structural health monitoring  
- 🏙️ Smart city disaster management  

---

## 🔮 Future Scope
- 🤖 Dynamic threshold adaptation using Machine Learning  
- ☁️ Cloud-based event logging (AWS / Firebase)  
- 📱 Mobile app alerts using MQTT  
- 🚑 Integration with emergency response systems  

---

## 👩‍💻 Author
Divya Lakshmi S  
B.E. Electronics and Communication Engineering  
Embedded Systems & IoT Enthusiast  

