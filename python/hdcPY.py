import numpy as np
from numpy import dot
from numpy.linalg import norm

def generate_random_vector(vector_size, empty=False):
    # Random vector generation
    if empty:
        random_vector = np.zeros(vector_size)
    else:
        random_vector = np.random.choice([-1, 1], vector_size)
        print(random_vector)
    return random_vector

def bind(vector_a, vector_b):
    # Binding operation (Hadamard product)
    bound_vector = np.multiply(vector_a, vector_b)
    return bound_vector

def bundle(vectors):
    # Bundling operation (Summation)
    bundled_vector = np.sum(vectors, axis=0)
    return bundled_vector

def normalize(vector):
    # L2 normalization (Euclidean normalization)
    norm = np.linalg.norm(vector)
    normalized_vector = vector / norm
    return normalized_vector

def clip(vector, min_value=-1, max_value=1):
    # Clipping operation
    clipped_vector = np.clip(vector, min_value, max_value)
    return clipped_vector

def shift(vector, shift_value):
    # Shifting operation
    shifted_vector = np.roll(vector, shift_value)
    return shifted_vector

def cosine_similarity(a, b):
    #check if divide by zero
    if(norm(a) * norm(b) == 0):
        return 0
    else:
        return dot(a, b)/(norm(a)*norm(b))
    
x = generate_random_vector(10000)
y = generate_random_vector(10000)

