from scipy.spatial.distance import pdist, squareform
import numpy as np

# Define the matrix
mat = np.array([
    [1.0, 2.0, 3.0],
    [4.0, 5.0, 6.0],
    [7.0, 8.0, 9.0]
])

# Compute the pairwise Euclidean distances between rows of the matrix
distances = pdist(mat, metric='euclidean')

# Convert the condensed distance matrix to a square form
square_distances = squareform(distances)

print(square_distances)
