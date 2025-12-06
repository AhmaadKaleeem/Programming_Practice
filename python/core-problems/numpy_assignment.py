#importing numpy
import numpy as np
# Creating a 1D NumPy array
array_1d = np.array([2, 4, 6, 8, 10])

# Creating a 2D NumPy array
array_2d = np.array([[1, 2, 3], [4, 5, 6]])

# Printing Properties
print("1-D Array Properties")
print(f"Array: {array_1d}")
print(f"Shape: {array_1d.shape}")
print(f"Dimensions: {array_1d.ndim}")
print(f"Data Type: {array_1d.dtype}")

# Minimum, maximum, mean, and standard deviation
print(f"Min: {np.min(array_1d)}")
print(f"Max: {np.max(array_1d)}")
print(f"Mean: {np.mean(array_1d)}")
print(f"Standard Deviation: {np.std(array_1d)}\n")

# --- Properties of the 2D Array ---
print("2-D Array Properties")
print(f"Array:\n{array_2d}")
print(f"Shape: {array_2d.shape}")
print(f"Dimensions: {array_2d.ndim}")
print(f"Data Type: {array_2d.dtype}")

# Minimum, maximum, mean, and standard deviation
print(f"Min: {np.min(array_2d)}")
print(f"Max: {np.max(array_2d)}")
print(f"Mean: {np.mean(array_2d)}")
print(f"Standard Deviation: {np.std(array_2d)}")

# Demo of Difference
A = np.array([[1, 2], [3, 4]])
B = np.array([[2, 0], [1, 3]])

# Element-wise multiplication
element_wise = A * B

# Dot product & Matrix multiplication
dot_product = np.dot(A, B)
matrix_mult = A @ B

print(f"Array A:\n{A}\n")
print(f"Array B:\n{B}\n")
print(f"Element-wise :\n{element_wise}\n")
print(f"Dot Product :\n{dot_product}\n")
print(f"Matrix Multiplication :\n{matrix_mult}")

# Demostrating 3-D Arrays 
v1 = np.array([1, 2, 3])
v2 = np.array([4, 5, 6])

# Calculate the dot product
dot_prod = np.dot(v1, v2)

# Calculate the cross product
cross_prod = np.cross(v1, v2)

print(f"Vector 1: {v1}")
print(f"Vector 2: {v2}\n")
print(f"Dot Product: {dot_prod}")
print(f"Cross Product: {cross_prod}\n")

# --- Explanations ---
# --- A ---
# The dot product returns a single scalar (a number).
# It represents the projection of one vector onto another. In ML/CV, it's used to measure similarity between vectors. 
# A dot product of 0 means the vectors are perpendicular to each other.
# It is the core operation in calculating the output of a neuron in a neural network (weights • inputs).
# --- B --- 
# The cross product returns another vector that is perpendicular to the plane
# formed by the original two vectors.
# In computer vision and graphics, it's used to calculate surface normals, which are
# essential for lighting calculations and determining the orientation of a surface.

# Demostating Stacking
v_stack = np.vstack((A, B))

# Horizontal stack
h_stack = np.hstack((A, B))

print(f"Vertical Stack :\n{v_stack}\n")
print(f"Horizontal Stack :\n{h_stack}")



# Generating a random 3x3 matrix
matrix = np.random.randint(1, 10, (3, 3))

# Performing operations
transpose = matrix.T
determinant = np.linalg.det(matrix)
eigenvalues, eigenvectors = np.linalg.eig(matrix)

print(f"Original Matrix:\n{matrix}\n")
print(f"Transpose:\n{transpose}\n")
print(f"Determinant: {determinant}\n")
print(f"Eigenvalues:\n{eigenvalues}\n")
print(f"Eigenvectors:\n{eigenvectors}\n")

# --- Explanation ---
# Eigenvalues and eigenvectors are properties of a square matrix.
# An eigenvector is a vector whose direction does not change when a linear transformation (the matrix) is applied to it. It is only scaled.
# The eigenvalue is the scalar factor by which the eigenvector is scaled.
# In short: A * v = λ * v (where A is the matrix, v is the eigenvector, λ is the eigenvalue).
# They are fundamental in many AI applications, like Principal Component Analysis (PCA)
# for dimensionality reduction, where they help find the principal components of the data.

# Demo Array Reshaping
# Given array
arr = np.array([1, 2, 3, 4, 5, 6, 7, 8, 9])

# Reshape into a 3x3 matrix
reshaped_arr = arr.reshape((3, 3))
print(f"Reshaped 3x3 Matrix:\n{reshaped_arr}\n")

# Extract the second row and third column
second_row = reshaped_arr[1, :]  # Row at index 1
third_col = reshaped_arr[:, 2]  # Column at index 2
print(f"Second Row: {second_row}")
print(f"Third Column: {third_col}\n")

# 3. Flatten it back to 1D
flattened_arr = reshaped_arr.flatten()
print(f"Flattened Array: {flattened_arr}")


# Q8
# Creating weight and input vectors
weights_1 = np.array([0.2, 0.5, 0.3])
weights_2 = np.array([0.4, 0.4, 0.2])
inputs = np.array([1.0, 2.0, 3.0])

# Compute neuron outputs using dot product
y1 = np.dot(weights_1, inputs)
y2 = np.dot(weights_2, inputs)
print(f"Neuron output y1 (before activation): {y1}")
print(f"Neuron output y2 (before activation): {y2}\n")

# Apply ReLU activation function
activated_y1 = np.maximum(0, y1)
activated_y2 = np.maximum(0, y2)
print(f"Neuron output y1 (after ReLU): {activated_y1}")
print(f"Neuron output y2 (after ReLU): {activated_y2}")

# Q9
# Given true and predicted values
y_true = np.array([1.0, 0.0, 1.0])
y_pred = np.array([0.8, 0.3, 0.4])

# 1. Compute loss for each sample
loss_per_sample = (y_pred - y_true)**2
print(f"Loss for each sample: {loss_per_sample}")

# 2. Compute the total mean loss
mean_loss = np.mean(loss_per_sample)
print(f"Total mean loss: {mean_loss}")

# Q10
# Create a random 5x5 square matrix A
A = np.random.rand(5, 5)

# Create a 5x5 identity matrix
I = np.identity(5)

# Verify the property A * I = A
result = A @ I

# Check if A and the result are "close enough" to account for floating-point inaccuracies
are_equal = np.allclose(A, result)

print(f"Matrix A:\n{A}\n")
print(f"Identity Matrix I:\n{I}\n")
print(f"Result (A @ I):\n{result}\n")
print(f"Is A @ I equal to A? {are_equal}")

# Q11
# Academic Dataset
X_academic = np.array([
    [85, 78, 92],  # Student 1
    [88, 80, 85],  # Student 2
    [75, 70, 65],  # Student 3
])

# Behavioral Dataset
X_behavioral = np.array([
    [90, 80, 85],  # Student 1
    [85, 70, 75],  # Student 2
    [60, 50, 55],  # Student 3
])

# Use Case 1: Horizontal Stack (combining features)
# Both datasets have the same students but different features.
X_combined = np.hstack((X_academic, X_behavioral))
print("--- Horizontal Stack (Combining Features) ---")
print(X_combined)
print("Shape:", X_combined.shape)
print("Each row now has 6 features: 3 academic + 3 behavioral.\n")

# Use Case 2: Vertical Stack (adding new samples)
# New data arrives for new students with the same 6 features.
X_new = np.array([
    [90, 82, 88, 95, 85, 90],  # New Student 4
    [78, 75, 70, 80, 70, 72]   # New Student 5
])

# Add these new samples under the existing combined dataset.
X_final = np.vstack((X_combined, X_new))
print("--- Vertical Stack (Adding New Students) ---")
print(X_final)
print("Shape:", X_final.shape)
print("The dataset now has 5 students, each with 6 features.")