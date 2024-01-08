from hdcPY import *
import numpy as np
import pandas as pd

N = 10000


def encodeAlphabet():
    vars = {}

    # from a to z and space using ascii code
    for letter in map(chr, range(ord('a'), ord('z')+1)):
        vars[letter] = generate_random_vector(N, empty=False)

    vars[' '] = generate_random_vector(N)
    
    alphabet = np.array(list(vars.values()))

    np.savetxt('python/alphabet.txt', alphabet, fmt='%f')

    print("saved alphabet to alphabet.txt")

    return vars

def loadAlphabet():
    alphabet = np.loadtxt('python/alphabet.txt')
    vars = {}
    i = 0
    for letter in map(chr, range(ord('a'), ord('z')+1)):
       
        vars[letter] = alphabet[i]
        i += 1

    vars[' '] = alphabet[i]

    return vars


def encodeSample(file_path, num_words=None):
    vars = loadAlphabet()
    
    language = generate_random_vector(N, empty=True)
    word_count = 0

    


    with open(file_path, 'r') as file:
        text = file.read().replace('\n', '')
        words = text.split()
        progress = 0

        for word in words:

            if num_words is not None and word_count >= num_words:
                break

            for i in range(len(word) - 2):
                trigram = word[i:i+3]

                # THE = rr(T)×r(H)×E
                first = shift(vars[trigram[0]], 2)
                second = shift(vars[trigram[1]], 1)
                third = vars[trigram[2]]
                
                
                trigramSum = bind(first, second)
                trigramSum = bind(trigramSum, third)

                language = bundle([language, trigramSum])

            word_count += 1
            progress += 1
            print(f"progress of {file_path}: " + str(progress) + "/" + str(len(words)))
            
    print("done encoding " + file_path)
    
   
    
    return normalize(language)


# x = generate_random_vector(N, empty=True)
# y = generate_random_vector(N, empty=False)
# z = generate_random_vector(N, empty=False)

# x = np.row_stack((x,y ))
# x = np.row_stack((x,z))


# print(x)
# x = bundle(x)
# print(x)