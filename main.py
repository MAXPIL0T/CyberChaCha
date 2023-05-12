import audio_tools
import extract_features

if __name__ == '__main__':
    extract_features.preprocess("Data\genres_original")
    extract_features.preprocess_model()