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
    signal = signal[:int(10 * sample_rate)] # truncate to 10 seconds
    mfccs = librosa.feature.mfcc(signal, n_mfcc=13, sr=sample_rate)
    return mfccs

# Loads a knn model for the GTANZ dataset
def load_model():
    # load the normalized data and various relevant info
    loaded_data = []
    with open("model.dat", "rb") as f:
        while True:
            try:
                loaded_data.append(pickle.load(f))
            except EOFError:
                break
    knn = loaded_data[0] # knn model used to classify, trained on GTANZ dataset
    mean = loaded_data[1]
    std_dev = loaded_data[2]
    min_length = loaded_data[3]

    return knn, mean, std_dev, min_length

# Trims and pads a given array of test instances to the specified length
def preprocess_test_instance(test_features, mean, std_dev, min_length):
    test_features = util.trim_arrays_to_length(test_features, min_length)
    # test_features = util.pad_arrays_with_zeros(test_features, min_length)
    test_features = normalize_with_vals(test_features, mean, std_dev) # original shape
    ninstances, coeff_num, frame_num = test_features.shape
    reshaped_test_features = test_features.reshape((ninstances, coeff_num * frame_num))
    return reshaped_test_features

# ------------------------ NORMALIZATION AND LOADING DATA --------------------------
# Normalizes data (to zero mean and unit variance) and returns the mean and std deviation used to normalize the data
def normalize(instances):
    num_frames = len(instances[0][0])
    reshaped = np.array(instances).reshape((len(instances), 13 * num_frames))
    mean = np.mean(reshaped, axis=0)
    std_dev = np.std(reshaped, axis=0)
    return normalize_with_vals(instances, mean, std_dev), mean, std_dev # original shape

# Normalizes data (also returns the scaler used on each frame in an array)
def normalize_with_vals(instances, mean, std_dev):
    num_frames = len(instances[0][0])
    reshaped = np.array(instances).reshape((len(instances), 13 * num_frames))
    reshaped_normalized = (reshaped - mean) / std_dev
    normalized = reshaped_normalized.reshape((len(instances), 13, num_frames)) # put it back in its original shape
    return normalized # original shape

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
    return {"mfcc": loaded_data[0], "classes": loaded_data[1]}

# ------------------------ OLD (USED WHEN WRITING THIS CODE) -------------------------- (not needed anymore but keep it just in case)
# Computes the accuracy of the model
def compute_accuracy():
    model, mean, std_dev, min_length = load_model()
    data = load_data()
    features = data["mfcc"] # these are 10 second long mfccs
    features = preprocess_test_instance(features, mean, std_dev, min_length) # reshaped
    labels = data["classes"]
    predictions = model.predict(features)
    print(accuracy_score(labels, predictions))
        
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
                    mfcc = extract_mfcc(os.path.join(dataset_path, dir, file_name))
                    data["mfcc"].append(mfcc.tolist()) # add the frames as a list as the features
                    data["classes"].append(label_index)
                    # pickle.dump(mfcc.tolist(), f) # store the features
                except:
                    continue
    pickle.dump(data["mfcc"], f) # store the features
    pickle.dump(data["classes"], f) # store the classes
    return data

# Stores pre-trained model
def preprocess_model():
    data = load_data() # raw mfccs and their classes
    min_length = util.get_min_length(data["mfcc"])
    features = data["mfcc"]
    labels = data["classes"]
    features = util.trim_arrays_to_length(features, min_length)
    # normalize the data
    features, mean, std_dev = normalize(features) # the mean and std_dev are used to normalize data

    # reshape into 2D array so we can use sklearn's knn
    ninstances, coeff_num, frame_num = features.shape
    reshaped_features = features.reshape((ninstances, coeff_num * frame_num))
    casted_labels = np.array(labels).astype(int) # cast labels as int

    # create the model
    knn = KNeighborsClassifier(n_neighbors=31, metric="minkowski", algorithm="brute")
    knn.fit(reshaped_features, casted_labels) # train the model

    # write data
    f = open("model.dat", "wb")
    pickle.dump(knn, f)
    pickle.dump(mean, f)
    pickle.dump(std_dev, f)
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