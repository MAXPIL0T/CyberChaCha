# Classify audio as a specific genre using KNN algorithm
import classification
import bpm_detection
import json
import util
import numpy as np

# Returns the genre of the audio (given by the file path of the wav file)
def classify_audio(file_path):
    # load model
    model, mean, std_dev, min_length = classification.load_model()
    # process the given audio instance
    mfccs = classification.extract_mfcc(file_path) # 10 second long mfcc
    preprocessed_instance = classification.preprocess_test_instance([mfccs], mean, std_dev, min_length) # reshaped
    return np.random.choice([model.predict(preprocessed_instance)[0], 1, 2, 3, 4, 5, 6, 7, 8, 9, 10], p=[0.5, 0.05, 0.05, 0.05, 0.05, 0.05, 0.05, 0.05, 0.05, 0.05, 0.05])

# Returns a random dance move based on the given genre / label
def get_random_move(label):
    with open("genre_to_dance.json") as f:
        data = json.load(f)
    return util.get_random_elem(data[str(label)])

# Returns the bpm tempo of the audio specified by the file path
def tempo(file_path):
    return bpm_detection.get_file_bpm(file_path)