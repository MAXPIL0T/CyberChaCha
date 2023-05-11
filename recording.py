import serial
import numpy as np
from scipy.io import wavfile
import time

PORT = 'COM5'
BAUD_RATE = 650000
DURATION = 10

# Initialize Serial port for reading audio data
ser = serial.Serial(PORT, BAUD_RATE)

data = []
# Recording start time
start_time = time.time()
# Until the time is over we record the audio
while True:
    # Value read from serial [between 0 and 4095]
    value = ser.readline().strip().decode()
    try:
        # Check if the value is actually a sensor reading and not junk, then add to dataset
        value = int(value)
        data.append(value)
    except ValueError:
        # If it is junk just go to then next serial reading
        pass

    # Check if recording is over, if it is break out of loop
    if time.time() - start_time >= DURATION:
        break

# Close Serial Port
ser.close()
# Transform data to numpy array
data = np.array(data)
# Normalize data to be between -1 and 1 for WAV file spec
data = (data / 4095.0) * 2 - 1
# Sample rate is determined by number of samples over duration
sample_rate = len(data) / DURATION

# Write this data to output.wav
wavfile.write('output.wav', int(sample_rate), data.astype(np.float32))