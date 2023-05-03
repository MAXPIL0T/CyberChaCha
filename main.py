import extract_features
import audio_tools

if __name__ == '__main__':
    result = audio_tools.classify_audio("Data\genres_original\hiphop\hiphop.00006.wav")
    print(audio_tools.get_random_move(result))