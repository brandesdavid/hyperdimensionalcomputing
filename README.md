# hyperdimensional computing in c and python

small library in python and c for hypervectors:
* bundling,
* binding,
* rotating/shifting
* and comparing (with hammer distance and cosine similarity)

## hypervectors

we use vectors with higher amounts of dimensions ( > 10000), that are representing to ideas, concepts or symbols.
with comparing methods like cosine similarity or the hammer distance, we can identify if any relations between
two hypervectors are disagreeing, agreeing or natural. 
a bipolar hypervector contain -1's and 1's. 

### bundling

we bundle two bipolar vectors by multiplying them element-wise, and using normalizing them to -1, 0 and 1 (using their signs)
through this operation, we can create a new hypervector that differs from the parent hypervectors. 
if we bundle the same hypervector, it stays exactly identical.

### binding

binding two bipolar hypervectors (adding them together), we create a new vector, that associates two vectors together. (making it generally dissimilar)
an important property of binding, is the reversibility. therefore, we can retrieve information
without creating noise.

### shifting

by rotating a vector through cyclic permutation, we can can create a new vector, that can hold information
like position in an alphabet based on the parent vector.

## example

in this repo, i've created a small languageguesser program (that kind of works).
it is based on this [stanford presentation](https://web.stanford.edu/class/ee380/Abstracts/171025-slides.pdf)
