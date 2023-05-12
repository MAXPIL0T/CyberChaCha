# Classify audio as a specific genre using KNN algorithm on GTZAN dataset
import extract_features
import bpm_detection
import librosa
import json
import util

# Returns the genre of the audio (given by the file path of the wav file)
def classify_audio(file_path):
    # load model
    model, mean, std_dev, min_length = extract_features.load_model()
    # process the given audio instance
    mfccs = extract_features.extract_mfcc(file_path) # 10 second long mfcc
    preprocessed_instance = extract_features.preprocess_test_instance([mfccs], mean, std_dev, min_length) # reshaped
    return model.predict(preprocessed_instance)[0]

# Returns a random dance move based on the given genre / label
def get_random_move(label):
    with open("genre_to_dance.json") as f:
        data = json.load(f)
    return util.get_random_elem(data[str(label)])

# Returns the bpm tempo of the audio specified by the file path
def tempo(file_path):
    return bpm_detection.get_file_bpm(file_path)