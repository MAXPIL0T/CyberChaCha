# Classify audio as a specific genre using KNN algorithm on GTZAN dataset
import extract_features
import librosa
import json
import util

# Returns the genre of the audio (given by the file path of the wav file)
def classify_audio(file_path):
    # load model
    model, scale_vals, min_length = extract_features.load_model()
    
    # process the given audio instance
    mfccs = extract_features.extract_mfcc(file_path)
    preprocessed_instance = extract_features.preprocess_test_instance([mfccs.T], min_length, scale_vals)
    return model.predict(preprocessed_instance)[0]

# Returns a random dance move based on the given genre / label
def get_random_move(label):
    with open("genre_to_dance.json") as f:
        data = json.load(f)
    return util.get_random_elem(data[str(label)])

# Returns the bpm tempo of the audio specified by the file path
# def tempo(file_path):
#     signal, sr = librosa.load(file_path)
#     onset_env = librosa.onset.onset_strength(signal, sr=sr)
#     return librosa.beat.tempo(onset_envelope=onset_env, sr=sr,
#                             aggregate=None)
    