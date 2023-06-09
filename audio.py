# Record audio in a circular queue from microphone (upload "RecordingAudioFromMX4466\RecordingAudioFromMX4466.ino" first)
import serial
import numpy as np
from scipy.io import wavfile
import time
import audio_tools

PORT = 'COM5' # microphone
PORT2 = 'COM6' # motors
BAUD_RATE = 650000
# Duration of individual sample in seconds
INDIVIDUAL_SAMPLE_DURATION = 1
# SAMPLE_QUEUE_SIZE * INDIVIDUAL_SAMPLE_DURATION = length in seconds
SAMPLE_QUEUE_SIZE = 10
WAIT_TIME = 5 # time in between each creation of a wav file

# Initialize Serial port for reading audio data
ser = serial.Serial(PORT, BAUD_RATE)
ser2 = serial.Serial(PORT2, BAUD_RATE)

# Counters
counter = 0
prev = 0

genre_dict = {1: "blues", 2: "classical", 3: "country", 4: "disco", 5: "hiphop", 6: "jazz", 7: "metal", 8: "pop", 9: "reggae", 10: "rock"}

# Makes a wav file and sends genre and tempo to PORT2
def create_wav(data):
    DURATION = len(data)
    # Flattens the data into a 1D array
    deep_copy = [item for sub_list in data for item in sub_list]
    # Transform deep_copy to numpy array
    deep_copy = np.array(deep_copy)
    # Normalize deep_copy data to be between -1 and 1 for WAV file spec, then scale for int16
    deep_copy = ((deep_copy / 4095.0) * 2 - 1)
    # Sample rate is determined by number of samples over duration
    sample_rate = len(deep_copy) / DURATION

    # Create File Name based on current time
    file_name = "output/{}.wav".format(time.time())
    # Write this data to output.wav
    wavfile.write(file_name, int(sample_rate), deep_copy.astype(np.float32))

    # Classify and send data
    genre = audio_tools.classify_audio(file_name)
    tempo = audio_tools.tempo(file_name)
    ser2.write(bytearray([genre]))
    ser2.write(bytearray([int(tempo)]))

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
            counter += 1
            # If our recording queue is full, remove the oldest chunk
            if len(data) >=  SAMPLE_QUEUE_SIZE:
                data.pop(0)
            # Add the chunk that was just recorded
            data.append(chunk)
            # Have the helper create the wav file for the current recording
            if len(data) >= 10 and counter > prev + WAIT_TIME: # need to wait for full 10 seconds and send every 5 seconds
                create_wav(data)
                prev = counter
            break
