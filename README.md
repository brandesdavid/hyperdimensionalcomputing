# setup

install numpy and run languagerecognizer.py

# hyperdimensional computing in c and python

small library in python and c for hypervectors:
* bundling,
* binding,
* rotating/shifting
* and comparing (with hammer distance and cosine similarity)

## hypervectors

we use vectors with higher amounts of dimensions ( sometimes even > 10000), that are representing to ideas, concepts or symbols.
with comparing methods like cosine similarity or the hammer distance, we can identify if any relations between
two hypervectors are disagreeing, agreeing or natural. 
a bipolar hypervector contain -1's and 1's. 

### bundling

we bundle two bipolar vectors by multiplying them element-wise, and using normalizing them to `-1, 0 and 1` (using their signs)
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
it is based from this [UC Berkeley stanford presentation](https://web.stanford.edu/class/ee380/Abstracts/171025-slides.pdf)

we read through a training data (en.txt) and cycle every trigram.
`hello` = `hel` + `ell` + `llo`.

we create randomly generate an N-size hypervectors {-1,1}, for every letter in the alphabet and the space char.
then, we bundle all the letters in a trigram, to bind all trigrams into one N-size hypervector.
the final hypervector represents our language, or the training text, that has been compiled.

by using the cosine similarity to another vector with this language vector and others, we can infer which
result is closer to 1. 

# results

this is the output from the tests and their language vectors.
it is pretty accurate, i think. 
take a look at the similarities in the tests and their designated languages.

french and italian score higher in closeness, as one could
infer from their roots.
```
english_test and english:  0.93
english_test and french:  0.51
english_test and german:  0.30
english_test and spanish:  0.43
english_test and italian:  0.43

french_test and english:  0.42
french_test and french:  0.94
french_test and german:  0.32
french_test and spanish:  0.62
french_test and italian:  0.55

german_test and english:  0.30
german_test and french:  0.36
german_test and german:  0.96
german_test and spanish:  0.29
german_test and italian:  0.33

spanish_test and english:  0.37
spanish_test and french:  0.62
spanish_test and german:  0.28
spanish_test and spanish:  0.95
spanish_test and italian:  0.63

italian_test and english:  0.40
italian_test and french:  0.60
italian_test and german:  0.33
italian_test and spanish:  0.66
italian_test and italian:  0.94
```
