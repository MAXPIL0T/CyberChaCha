import numpy as np

# Returns the 2D array that was reshaped from the inputted 1D array into dim_x by dim_y
def reshape_1D_to_2D(arr, dim_x, dim_y):
    return np.reshape(arr, (dim_x, dim_y))

# Returns the min length of an array inside the given 3D array
def get_min_length(big_arr):
    min_length = float('inf')
    for med_arr in big_arr:
        for small_arr in med_arr:
            if len(small_arr) < min_length:
                min_length = len(small_arr)
    return min_length

# trims all the given arrays to the size of the smallest array, returns the size of the smallest array
def trim_arrays_to_min_length(arrays):
    min_length = min([len(arr) for arr in arrays])
    trim_arrays_to_length(arrays, min_length)
    return min_length

# trims all given arrays to the given length
def trim_arrays_to_length(arrays, length):
    copy_arr = make_3d_with_length(len(arrays), length)
    for i in range(len(arrays)): # for each instance
        inst = arrays[i]
        for j in range(len(inst)):
            copy_arr[i][j] = arrays[i][j][0:length]
    return copy_arr
    
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
    arr_copy = make_3d_with_length(len(arrays), end_length)
    for i in range(len(arrays)):
        instance = arrays[i]
        for j in range(len(instance)):
            coef_arr = instance[j]
            if len(coef_arr) < end_length:
                new_arr = np.concatenate((coef_arr, [0] * (end_length - len(coef_arr))), axis=0)
                arr_copy[i][j] = new_arr
    return arrays

def get_random_elem(arr):
    return np.random.choice(arr)

def make_3d_with_length(num_instances, length):
    arr = []
    for i in range(num_instances):
        inst_arr = []
        for _ in range(13):
            inst_arr.append([0] * length)
        arr.append(inst_arr)
    return arr