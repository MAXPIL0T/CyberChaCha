# Extract features from audio using Mel Frequency Cepstral Coefficients

import librosa
import os
import pickle
import util
import numpy as np
from sklearn.utils import shuffle
from sklearn.model_selection import train_test_split
from sklearn.neighbors import KNeighborsClassifier
from sklearn.metrics import accuracy_score

# ------------------------ USEFUL FOR PROJECT --------------------------
# Returns a matrix of mel frequency cepstral coefficients (13 rows, one for each coefficient vs columns for frames)
def extract_mfcc(file_name):
    signal, sample_rate = librosa.load(file_name)
    mfccs = librosa.feature.mfcc(signal, n_mfcc=13, sr=sample_rate)
    return mfccs

# Loads a knn model for the GTANZ dataset
def load_model():
    # load the normalized data and various relevant info
    loaded_data = []
    with open("normalized_data.dat", "rb") as f:
        while True:
            try:
                loaded_data.append(pickle.load(f))
            except EOFError:
                break
    features = np.array(loaded_data[0]) # all the features of every instance in the dataset
    labels = np.array(loaded_data[1]) # corresponding labels
    scale_vals = loaded_data[2] # values used to normalize the dataset instances
    min_length = loaded_data[3] # minimum length of the instances in the dataset (i.e min number of frames)

    # reshape into 2D array so we can use sklearn's knn
    ninstances, frame_num, coeff_num = features.shape
    reshaped_features = features.reshape((ninstances, frame_num * coeff_num))
    casted_labels = labels.astype(int) # cast labels as int

    # create the model using a custom comparison_metric (see below)
    knn = KNeighborsClassifier(n_neighbors=28, metric=comparison_metric, metric_params={"dim_x": frame_num, "dim_y": coeff_num}, algorithm='brute')
    knn.fit(reshaped_features, casted_labels) # train the model
    return (knn, scale_vals, min_length)

# Comparison metric used to calculate distance between two instance
    # inst1 and inst2 are both arrays of vectors, where each vector is a frame
    # each instance is then reshaped into dim_x by dim_y array (frame number by coefficients number)
def comparison_metric(inst1, inst2, dim_x, dim_y):
    # reshape the instances into 2D arrays
    inst1 = util.reshape_1D_to_2D(inst1, dim_x, dim_y)
    inst2 = util.reshape_1D_to_2D(inst2, dim_x, dim_y)
    distances_between_each_frame = [np.linalg.norm(frame1 - frame2) for frame1, frame2 in zip(inst1, inst2)]
    return np.average(distances_between_each_frame) # "distance" between two instances is the average distance between their frames

# Trims and pads a given array of test instances to the specified length
def preprocess_test_instance(test_features, length, scale_vals):
    util.trim_arrays_to_length(test_features, length)
    # test_features = np.array(test_features)
    normalize_with_scale_vals(test_features, scale_vals)
    test_features = util.pad_arrays_with_zeros(test_features, length)
    # reshape
    test_features = np.array(test_features)
    ninstances, frame_num, coeff_num = test_features.shape
    reshaped_test_features = test_features.reshape((ninstances, frame_num * coeff_num))
    return reshaped_test_features

# ------------------------ NORMALIZATION AND LOADING DATA --------------------------
# Normalizes data in-place (also returns the scale values used on each frame in an array)
def normalize(data, flattened_frames):
    scale_vals = []
    for i in range(len(flattened_frames)):
        mean = np.mean(flattened_frames[i])
        std_dev = np.std(flattened_frames[i])
        scale_vals.append((mean, std_dev))
    return normalize_with_scale_vals(data, scale_vals)

# Normalizes data in-place (also returns the scalers used on each frame in an array)
def normalize_with_scale_vals(data, scale_vals):
    for i in range(len(data[0])): # for each frame
        mean = scale_vals[i][0]
        std = scale_vals[i][1]
        for j in range(len(data)): # for each instance
            frame = data[j][i]
            data[j][i] = transform(mean, std, data[j][i]) # normalize the data
    return scale_vals

# Transforms arr by using mean normalization with the given mean and std
def transform(mean, std, arr):
    return np.divide(np.subtract(arr, mean), std)

# Loads data from binary file (all raw mfccs data) and returns it
def load_data():
    loaded_data = []
    with open("all_mfcc.dat", "rb") as f:
        while True:
            try:
                loaded_data.append(pickle.load(f))
            except EOFError:
                break
    return {"mfcc": loaded_data[:-1], "classes": loaded_data[-1]}

# ------------------------ OLD (USED WHEN WRITING THIS CODE) -------------------------- (not needed anymore but keep it just in case)
# Shuffles and splits data into training and test sets
def split_data(data):
    features = np.array(data["mfcc"], dtype=object)
    classes = np.array(data["classes"], dtype=object)
    shuffle(features, classes)
    return train_test_split(features, classes, test_size=0.2, train_size=0.8, shuffle=False) # features_train, features_test, labels_train, labels_test

# Returns data as mfcc and classes (also dumps mfccs into a binary file)
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

# Stores pre-trained model
def preprocess_model():
    data = load_data()
    min_length = util.trim_arrays_to_min_length(data["mfcc"])
    features = data["mfcc"]
    labels = data["classes"]
    scale_vals = normalize(features, util.get_flattened_frames(features)) # the scale vals (mean and variance fits) are used to normalize the training data

    f = open("normalized_data.dat", "wb")
    pickle.dump(features, f)
    pickle.dump(labels, f)
    pickle.dump(scale_vals, f)
    pickle.dump(min_length, f)

# Compute distance between two audio files given by the file paths
def distance(path1, path2):
    features1 = np.array([extract_mfcc(path1).T])
    features2 = np.array([extract_mfcc(path2).T])

    # trim, normalize, pad
    min_length = util.trim_arrays_to_min_length(features1)
    scale_vals = normalize(features1, util.get_flattened_frames(features1))
    normalize_with_scale_vals(features2, scale_vals)
    util.trim_arrays_to_length(features2, min_length)
    features2 = util.pad_arrays_with_zeros(features2, min_length)

    # reshape
    ninstances1, frame_num1, coeff_num1 = features1.shape
    reshaped1 = features1.reshape((ninstances1, frame_num1 * coeff_num1))
    ninstances2, frame_num2, coeff_num2 = features2.shape
    reshaped2 = features2.reshape((ninstances2, frame_num2 * coeff_num2))

    return comparison_metric(reshaped1, reshaped2, frame_num1, coeff_num1)