import serial
import numpy as np
from scipy.io import wavfile
import time

PORT = 'COM5'
BAUD_RATE = 650000
DURATION = 10

ser = serial.Serial(PORT, BAUD_RATE)

data = []
start_time = time.time()
while True:
    value = ser.readline().strip().decode()
    try:
        value = int(value)
        data.append(value)
    except ValueError:
        pass

    if time.time() - start_time >= DURATION:
        break

ser.close()
data = np.array(data)
data = (data / 4095.0) * 2 - 1
sample_rate = len(data) / DURATION

wavfile.write('output.wav', int(sample_rate), data.astype(np.float32))
