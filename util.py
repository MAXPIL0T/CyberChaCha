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

# Returns a random element from the given array
def get_random_elem(arr):
    return np.random.choice(arr)

# Makes a 3D array with 2nd dimension = 13 and 3rd dimension = length
def make_3d_with_length(num_instances, length):
    arr = []
    for i in range(num_instances):
        inst_arr = []
        for _ in range(13):
            inst_arr.append([0] * length)
        arr.append(inst_arr)
    return arr