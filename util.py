import numpy as np

# Returns the 2D array that was reshaped from the inputted 1D array into dim_x by dim_y
def reshape_1D_to_2D(arr, dim_x, dim_y):
    return np.reshape(arr, (dim_x, dim_y))

# trims all the given arrays to the size of the smallest array, returns the size of the smallest array
def trim_arrays_to_min_length(arrays):
    min_length = min([len(arr) for arr in arrays])
    trim_arrays_to_length(arrays, min_length)
    return min_length

# trims all given arrays to the given length
def trim_arrays_to_length(arrays, length):
    for i in range(len(arrays)):
        arrays[i] = arrays[i][0:length]
    
# returns an array with each entry being an array of all the values belonging to a particular frame
    # ex. first entry of the returned array is an array of every value in frame 1 of every instance in data
    # data is a 3D array: num_instances x frame_num x coeffs_num
def get_flattened_frames(data):
    num_frames = len(data[0])
    frames = []
    for i in range(num_frames):
        frame_all = []
        frame_all = frame_all + [inst[i] for inst in data] # get the values from the correct frame in each instance
        frames.append(np.array(frame_all))
    return frames

# Pad every array inside arrays to the end_length with zeros
def pad_arrays_with_zeros(arrays, end_length):
    for i in range(len(arrays)): # for each array (has frames)
        if len(arrays[i]) < end_length: # if not enough frames
            zero_arrs = np.zeros((end_length - len(arrays[i]), 13))
            arrays[i] = np.concatenate((np.array(arrays[i]), zero_arrs), axis=0)
    return arrays