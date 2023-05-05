import time

import numpy as np
import serial
from scipy.io import wavfile

PORT = '/dev/cu.usbserial-10'
BAUD_RATE = 230400
DURATION = 1
COUNT = 1

# Initialize Serial port for reading audio data
ser = serial.Serial(PORT, BAUD_RATE)

data = []
sendData = []
for x in range(6):
    # Recording start time
    start_time = time.time()
    # Until the time is over we record the audio
    while True:
        # Value read from serial [between 0 and 4095]
        value = ser.readline().strip().decode()
        print(value)
        try:
            # Check if the value is a sensor reading and not junk, add dataset
            value = int(value)
            if COUNT >= 5:
                data.pop(0)
                data.append(value)
            else:
                data.append(value)
        except ValueError:
            # If it is junk just go to then next serial reading
            pass

        # Check if recording is over, if it is break out of loop
        if time.time() - start_time >= DURATION:
            break

    # Close Serial Port
    # ser.close()
    # Transform data to numpy array
    sendData = np.array(data)
    # Normalize data to be between -1 and 1 for WAV file spec
    sendData = (sendData / 4095.0) * 2 - 1
    # Sample rate is determined by number of samples over duration
    sample_rate = len(sendData) / COUNT

    # Write this data to output.wav
    # wavfile.write('output'+str(x+1)+'.wav', int(sample_rate), sendData.astype(np.float32))
    wavfile.write('output'+'.wav', int(sample_rate), sendData.astype(np.int16))
    # sendData = []
    print(len(data))
    if COUNT < 5:
        COUNT += 1

