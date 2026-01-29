# Earthquake-stabilization-system
# Seismic Detection System

A real-time embedded system designed to detect seismic vibrations using two independent nodes that communicate and validate data collaboratively to generate a reliable earthquake alert.

## Problem Statement
Earthquakes and tremors can cause serious damage and risk to human life. Most low-cost systems suffer from false alerts due to noise and lack of cross-validation.

## Objective
To design a system that:
- Independently detects seismic waves using two embedded nodes  
- Exchanges sensor data between nodes using MAC-based communication  
- Compares values with a predefined threshold  
- Classifies the event as either a false alert or a true earthquake  

## Features
- Dual-node independent seismic detection  
- Mutual data validation to reduce false positives  
- Threshold-based decision algorithm  
- Real-time alert generation  
- Reliable and scalable embedded design  

## Hardware Components
- ESP32-WROOM-32 Microcontroller (2 units)  
- ADXL345 / MPU6050 MEMS Accelerometer (2 units)  
- Piezoelectric Vibration Sensor (SW-420) (2 units)  
- Buzzer / LED Indicator  
- Breadboard and Jumper Wires  
- 5V Power Supply / USB Power  

## Software & Tools
- Arduino IDE  
- Embedded C  
- ESP32 Wi-Fi / Bluetooth Stack  
- MAC Address-based Peer-to-Peer Communication  

## How It Works
Both System 1 and System 2 continuously monitor ground vibrations using MEMS sensors.  
Each system processes its own sensor data locally and compares it with a predefined threshold.  
The processed data is then exchanged between the two systems using MAC-based wireless communication.  
If both systems confirm abnormal values beyond the threshold, the event is classified as a **True Earthquake**.  
If only one system detects abnormal activity, it is classified as a **False Alert**.

## Applications
- Earthquake early warning systems  
- Hospital and dialysis center safety  
- Structural health monitoring  
- Smart city disaster management  

## Future Scope
- Dynamic threshold adaptation using Machine Learning  
- Cloud-based event logging (AWS / Firebase)  
- Mobile app alerts using MQTT  
- Integration with emergency response systems  

## Author
Divya Lakshmi S  
B.E. Electronics and Communication Engineering  
Embedded Systems & IoT Enthusiast
