# hyperdimensional computing

import numpy as np

class HDV:
    def __init__(self, N, empty=False):
        self.N = N
        if empty:
            self.hdv = np.zeros(N)
        else:
            self.hdv = np.random.choice([-1, 1], size=N)
    
    def compare(self, other):
        return (self.hdv == other.hdv).sum()
    
    def Bind(self, other):
        self.hdv = self.hdv * other.hdv

    def Bundle(self, other):
        self.hdv = np.sign(self.hdv + other.hdv)

    def Shift(self, shift=1):
        self.hdv = np.roll(self.hdv, shift)

    def cosine_similarity(self, other):
        return np.dot(self.hdv, other.hdv) / (np.linalg.norm(self.hdv) * np.linalg.norm(other.hdv))



def generateHDV(N, empty=False):
    if empty:
        return np.zeros(N)
    else:
        return np.random.choice([-1, 1], size=N)

# produce a new vector that is dissimilar to the original
def Bind(a, b):
    return a * b

# bundle two vectors together
def Bundle(a, b):
    sum = a + b
    return sum

def Quantize(a):
    return a-1

# check the similarity of two hypervectors   
def cosine_similarity(a, b):
    dot_product = np.dot(a, b)
    norm_a = np.linalg.norm(a)
    norm_b = np.linalg.norm(b)
    return dot_product / (norm_a * norm_b)
    
def Shift(a, shift=1):
    return np.roll(a, shift)

def compare(a, b):
    return (a == b).sum()

x = generateHDV(5)
y = generateHDV(5)

print("x:              ", x)
print("y:              ", y)

y = Bundle(x, y)   
print("bundling:       ", y)
y = Quantize(y)
print("quantizing:     ", y)

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