# Extract features from audio using Mel Frequency Cepstral Coefficients

import librosa
import os
import pickle
import numpy as np
from sklearn.utils import shuffle
from sklearn.model_selection import train_test_split
from sklearn.preprocessing import StandardScaler
from sklearn.neighbors import KNeighborsClassifier
from sklearn.metrics import accuracy_score
# import matplotlib.pyplot as plt

# returns a matrix of mel frequency cepstral coefficients (13 rows, one for each coefficient vs columns for frames)
def extract_mfcc(file_name):
    signal, sample_rate = librosa.load(file_name)
    mfccs = librosa.feature.mfcc(signal, n_mfcc=13, sr=sample_rate)
    return mfccs

# returns data as mfcc and classes (also dumps mfccs into a binary file)
def preprocess(dataset_path):
    f = open("all_mfcc.dat", "wb")
    data = {"mfcc": [], "classes": []}
    # os.walk returns a generator that creates a tuple of values (current path, directories in current path, files in current path)
    # enumerate returns an iterator
    for label_index, (path, dirs, files) in enumerate(os.walk(dataset_path)): # for example, label_index = 1 for all files in the "blues" folder
        for file_name in sorted(files):
            if file_name.endswith(".wav"):
                dir = file_name.split(".")[0]
                try:
                    mfcc = extract_mfcc(os.path.join(dataset_path, dir, file_name)).T
                    data["mfcc"].append(mfcc.tolist()) # add the frames as a list as the features
                    data["classes"].append(label_index)
                    pickle.dump(mfcc.tolist(), f) # store the features
                except:
                    continue
    pickle.dump(data["classes"], f) # store the classes
    return data

# Loads data from binary file and returns it
def load_data():
    loaded_data = []
    with open("all_mfcc.dat", "rb") as f:
        while True:
            try:
                loaded_data.append(pickle.load(f))
            except EOFError:
                break
    return {"mfcc": loaded_data[:-1], "classes": loaded_data[-1]}

# shuffles and splits data into training and test sets
def split_data(data):
    features = np.array(data["mfcc"], dtype=object)
    classes = np.array(data["classes"], dtype=object)
    shuffle(features, classes)
    return train_test_split(features, classes, test_size=0.2, train_size=0.8, shuffle=False) # features_train, features_test, labels_train, labels_test

# returns an array with each entry being an array of all the values belonging to a particular frame
def get_flattened_frames(data):
    num_frames = len(data[0])
    frames = []
    for i in range(num_frames):
        print("i = " + str(i))
        frame_all = []
        frame_all = frame_all + [inst[i] for inst in data] # get the values from the correct frame in each instance
        frames.append(frame_all)
    return frames

# trims all the given arrays to the size of the smallest array, returns the size of the smallest array
def trim_arrays_to_min_length(arrays):
    min_length = min([len(arr) for arr in arrays])
    for i in range(len(arrays)):
        arrays[i] = arrays[i][0:min_length]
    return min_length

# normalizes data in-place (also returns the scalers used on each frame in an array)
def normalize(data, flattened_frames):
    scalers = []
    for i in range(len(flattened_frames)):
        scaler = StandardScaler()
        scaler.fit(flattened_frames[i])
        scalers.append(scaler)
    return normalize_with_scalers(data, scalers)

# normalizes data in-place (also returns the scalers used on each frame in an array)
def normalize_with_scalers(data, scalers):
    for i in range(len(data[0])): # for each frame
        for j in range(len(data)): # for each instance
            frame = data[j][i]
            data[j][i] = scaler[i].transform(frame) # normalize the data
    return scalers

# comparison metric used to calculate distance between two instance
# inst1 and inst2 are both arrays of vectors, where each vector is a frame
def comparison_metric(inst1, inst2):
    distances_between_each_frame = [np.linalg.norm(frame1 - frame2) for frame1, frame2 in zip(inst1, inst2)]
    return np.average(distances_between_each_frame)

# returns the accuracy of knn over the GTANZ dataset for varying values of k
def compute_accuracy(dataset_path):
    k_vals = [5]
    accuracy_vals = []
    data = preprocess(dataset_path)
    for k in k_vals:
        knn = KNeighborsClassifier(n_neighbors=k, metric=comparison_metric)
        features_train, features_test, labels_train, labels_test = split_data(data)
        scalers = normalize(features_train, get_flattened_frames(features_train)) # the scalers (mean and variance fits) used to normalize the training data
        normalize_with_scalers(features_test, scalers) # normalize the testing instances with the same scalers

        knn.fit(features_train, labels_train) # train the model

        # compute accuracy
        predictions = knn.predict(features_test)
        accuracy = accuracy_score(labels_test, predictions)
        accuracy_vals.append(accuracy)
    return (k_vals, accuracy_vals)