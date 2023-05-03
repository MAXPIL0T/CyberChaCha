# Classify audio as a specific genre using KNN algorithm on GTZAN dataset
import extract_features

# Returns the genre of the audio (given by the file path of the wav file)
def classify_audio(file_path):
    # load model
    model, scale_vals, min_length = extract_features.load_model()
    
    # process the given audio instance
    mfccs = extract_features.extract_mfcc(file_path)
    preprocessed_instance = extract_features.preprocess_test_instance([mfccs.T], min_length, scale_vals)
    return model.predict(preprocessed_instance)[0]