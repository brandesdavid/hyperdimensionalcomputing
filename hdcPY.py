# hyperdimensional computing

import numpy as np

class HDC:
    # this creates a bipolar vector of size n
    def generate(N, empty=False):
        if empty:
            return np.zeros(N)
        else:
            return np.random.choice([-1, 1], size=N)

    # creates a matrix of hypervectors 
    def HDV(rowSize, N):
        return np.random.choice([-1, 1], size=(rowSize, N))

    # this compares two bipolar vectors and returns the number of matching elements
    # it should be equal to about n/2
    def compare(a, b):
        return (a == b).sum()

    # produce a new vector that is dissimilar to the original
    def Bind(a, b):
        return a * b

    def Bundle(a, b):
        return np.sign(a + b)

    # create a new vector through shifting, to
    def Shift(hdv, shift=1):
        return np.roll(hdv, shift)

    # check the similarity of two hypervectors   
    def cosine_similarity(a, b):
        return np.dot(a, b) / (np.linalg.norm(a) * np.linalg.norm(b))
    




# def print():
#     x = generateHDV(N)
#     y = generateHDV(N)

#     print("x:              ", x)
#     print("y:              ", y)

#     print("comparing:      ", compare(x, y))
#     print(" ")
#     print("Binding:        ", Bind(x, y))

#     print("reversing to x: ", Bind(Bind(x, y), y))
#     print("x:              ", x)

#     print(" ")
#     print("x:              ", x)
#     print("y:              ", y)

#     print("bundling:       ", Bundle(x, y))