import serial
import numpy as np
from scipy.io import wavfile
import time

PORT = 'COM6'
BAUD_RATE = 650000
# Duration of individual sample in seconds
INDIVIDUAL_SAMPLE_DURATION = 1
# SAMPLE_QUEUE_SIZE * INDIVIDUAL_SAMPLE_DURATION = length in seconds
SAMPLE_QUEUE_SIZE = 10

# Initialize Serial port for reading audio data
ser = serial.Serial(PORT, BAUD_RATE)

def create_wav(data):
    DURATION = len(data)
    # Flattens the data into a 1D array
    deep_copy = [item for sub_list in data for item in sub_list]
    # Transform deep_copy to numpy array
    deep_copy = np.array(deep_copy)
    # Normalize deep_copy data to be between -1 and 1 for WAV file spec, then scale for int16
    deep_copy = 32767 * ((deep_copy / 4095.0) * 2 - 1)
    # Sample rate is determined by number of samples over duration
    sample_rate = len(deep_copy) / DURATION

    # Create File Name based on current time
    file_name = "{}.wav".format(time.time())
    # Write this data to output.wav
    wavfile.write(file_name, int(sample_rate), deep_copy.astype(np.int16))

    # TODO: Once wav file is created we should pass it to the classifier here. Should use threading for this

data = []
while True:
    # Recording start time
    start_time = time.time()
    # Until the time is over we record the audio
    chunk = []
    while True:
        # Value read from serial [between 0 and 4095]
        value = ser.readline().strip().decode()
        try:
            # Check if the value is a sensor reading and not junk, add dataset
            value = int(value)
            chunk.append(value)
        except ValueError:
            # If it is junk just go to then next serial reading
            pass
        
        # Check if recording is over, if it is break out of loop
        if time.time() - start_time >= INDIVIDUAL_SAMPLE_DURATION:
            # If our recording queue is full, remove the oldest chunk
            if len(data) >=  SAMPLE_QUEUE_SIZE:
                data.pop(0)
            # Add the chunk that was just recorded
            data.append(chunk)
            # Have the helper create the wav file for the current recording
            create_wav(data)
            break
