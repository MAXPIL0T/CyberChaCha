# Extract features from audio using Mel Frequency Cepstral Coefficients

import librosa
import librosa.display
import matplotlib.pyplot as plt

# returns a matrix of mel frequency cepstral coefficients (13 rows, one for each coefficient vs columns for frames)
def extract_mfcc(file_name):
    signal, sample_rate = librosa.load(file_name)
    mfccs = librosa.feature.mfcc(signal, n_mfcc=13, sr=sample_rate)
    return mfccs