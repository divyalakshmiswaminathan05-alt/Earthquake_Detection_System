// ESP32 + AD8232 Real-Time ECG Plot

#include <Arduino.h> // Required for ESP32 in some IDE setups

const int ECG_PIN = 34; // AD8232 OUTPUT connected to GPIO34
int ecgValue = 0;

void setup() {
  Serial.begin(115200);   // Serial Monitor / Serial Plotter
  pinMode(ECG_PIN, INPUT);
}

void loop() {
  ecgValue = analogRead(ECG_PIN); // read ECG analog value

  // Optional: Simple smoothing filter (moving average)
  static float smoothedValue = 0;
  smoothedValue = 0.1 * ecgValue + 0.9 * smoothedValue;

  Serial.println(smoothedValue);   // print value for plotting
  delay(200); // ~500Hz sampling rate
}
