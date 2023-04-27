import extract_features

if __name__ == '__main__':
    data = extract_features.load_data()
    features_train, features_test, labels_train, labels_test = extract_features.split_data(data)
    min_length = extract_features.trim_arrays_to_min_length(features_train)
    extract_features.get_flattened_frames(features_train)