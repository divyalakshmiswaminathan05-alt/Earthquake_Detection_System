import serial
import time
import matplotlib.pyplot as plt
import numpy as np
from scipy.signal import find_peaks

# --- Serial Setup ---
ser = serial.Serial('COM3', 115200)  # Change COM port if needed
time.sleep(2)

# --- Data Storage ---
ecg_data = []
k_values = []
time_axis = []

# Initial potassium level
k_ions = 4.0

# --- Real-time Data Capture ---
start_time = time.time()

while len(time_axis) < 150:  # 150 seconds of data
    if ser.in_waiting > 0:
        try:
            line = ser.readline().decode('utf-8').strip()
            values = line.split(',')

            if len(values) == 2:
                ecg_val = int(values[0])  # ECG
                accel_val = float(values[1])  # Accelerometer (not used here)

                t = time.time() - start_time

                ecg_data.append(ecg_val)
                time_axis.append(t)

                # --- Detect ECG Peaks (possible T-waves) ---
                if len(ecg_data) > 50:  # wait until we have some data
                    # Use last 50 samples as a window
                    window = np.array(ecg_data[-50:])
                    peaks, _ = find_peaks(window, height=np.mean(window) + 2 * np.std(window))

                    # If any peaks found in this window -> increment potassium
                    if len(peaks) > 0:
                        k_ions += 0.01  # simulate rising K+

                k_values.append(k_ions)
        except:
            pass

ser.close()

# --- Plot Results ---
plt.figure(figsize=(10, 6))

plt.subplot(2, 1, 1)
plt.plot(time_axis, ecg_data, color='blue')
plt.title("ECG Signal vs Time")
plt.ylabel("ECG")

plt.subplot(2, 1, 2)
plt.plot(time_axis, k_values, color='red')
plt.xlabel("Time (s)")
plt.ylabel("K⁺ Ions")

plt.show()
