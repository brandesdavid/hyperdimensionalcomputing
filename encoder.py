from hdcPY import *
import numpy as np

N = 10000


def encodeAlphabet():
    vars = {}

    # from a to z and space using ascii code
    for letter in map(chr, range(ord('a'), ord('z')+1)):
        vars[letter] = generateHDV(N)

    vars[' '] = generateHDV(N)
    
    alphabet = np.array(list(vars.values()))

    np.savetxt('alphabet.txt', alphabet, fmt='%u')

    print("saved alphabet to alphabet.txt")

    return vars

def loadAlphabet():
    alphabet = np.loadtxt('alphabet.txt')
    vars = {}
    i = 0
    for letter in map(chr, range(ord('a'), ord('z')+1)):
       
        vars[letter] = alphabet[i]
        i += 1

    vars[' '] = alphabet[i]

    return vars

def encodeSample(file_path, num_words=None):
    vars = loadAlphabet()
    
    language = generateHDV(N, empty=True)
    word_count = 0

    with open(file_path, 'r') as file:
        text = file.read().replace('\n', '')
        words = text.split()
        for word in words:
            if num_words is not None and word_count >= num_words:
                break
            for i in range(len(word) - 2):
                trigram = word[i:i+3]

                # THE = rr(T)×r(H)×E
                first = Shift(vars[trigram[0]], 2)
                second = Shift(vars[trigram[1]], 1)
                third = vars[trigram[2]]
                
                trigramSum = Bind(Bind(first, second), third)

                language = Bundle(language, trigramSum)
            word_count += 1
    return language


# saving english
# lang = encodeSample('en.txt')
# np.savetxt('vec_en.txt', lang, fmt='%u')


# saving french
# lang = encodeSample('fr.txt')
# np.savetxt('vec_fr.txt', lang, fmt='%u')

french = np.loadtxt('vec_fr.txt')
english = np.loadtxt('vec_en.txt')

test = encodeSample('test.txt')
print("test and english", cosine_similarity(test, english))
print("test and french", cosine_similarity(test, french))