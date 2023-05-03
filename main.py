import extract_features
import audio_classify

if __name__ == '__main__':
    result = extract_features.distance("Data\genres_original\metal\metal.00000.wav", "Data/genres_original/blues/blues.00003.wav")
    print(result)