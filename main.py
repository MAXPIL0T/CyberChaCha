import extract_features
import util
import numpy as np
from speechpy.processing import cmvn
import pickle
import audio_tools
from sklearn.metrics import accuracy_score

if __name__ == '__main__':
    extract_features.preprocess_model()