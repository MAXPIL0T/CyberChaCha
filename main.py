import extract_features
import audio_classify

if __name__ == '__main__':
    result = audio_classify.classify_audio("Data\genres_original\hiphop\hiphop.00006.wav")
    print(result)