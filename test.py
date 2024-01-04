from hdcPY import HDC
import numpy as np

N = 500000


variables = {}

#  from a to z using ascii code
for letter in map(chr, range(ord('a'), ord('z')+1)):
    variables[letter] = HDC.generate(N)


# e.g: som = rr(s)×r(o)×m
def encode(word):
    TrigramsArray = []
    for i in range(0, len(word)-2, 1):
        substring = word[i:i+3]
        
        first = variables[chr(ord(substring[0]))]
        second = variables[chr(ord(substring[1]))]
        third = variables[chr(ord(substring[2]))]
        
        #print(substring)

        trigram = HDC.Bind(HDC.Bind(HDC.Shift(HDC.Shift(first)), HDC.Shift(second)), third)
        TrigramsArray += [trigram]

    language = HDC.generate(N, empty=True)     

    for trigram in TrigramsArray:
        language = HDC.Bundle(language, trigram)
    return language


def encodeFile(path='words.txt', num_lines=None):
    TrigramsArray = []
    line_count = 0
    with open(path, 'r') as file:
        for line in file:
            if num_lines is not None and line_count == num_lines:
                break
            word = line.strip()
        
            for i in range(0, len(word)-2, 1):
                substring = word[i:i+3]
                
                first = variables[chr(ord(substring[0]))]
                second = variables[chr(ord(substring[1]))]
                third = variables[chr(ord(substring[2]))]
                
                trigram = HDC.Bind(HDC.Bind(HDC.Shift(HDC.Shift(first)), HDC.Shift(second)), third)
                TrigramsArray += [trigram]
                
            line_count += 1
    
    language = HDC.generate(N, empty=True)     

    for trigram in TrigramsArray:
        language = HDC.Bundle(language, trigram)
    return language


def encodeSaveLang(path):
    lang = encodeFile(path=path, num_lines=50000)
    np.savetxt('vec_'+path, lang, fmt='%d')

def loadLang(path='words_vec.txt'):
    return np.loadtxt(path, dtype=int)



# encodeSaveLang(path='english_words.txt')
# encodeSaveLang(path='french_words.txt')

# french = loadLang(path='vec_french_words.txt')
# english = loadLang(path='vec_english_words.txt')

def success_rate():
    # ---- testing ----
    total_count = 0
    success_count = 0

    # Open the file
    with open('english_words.txt', 'r') as file:
        # Iterate over each line in the file
        for line in file:
            word = line.strip()

            total_count += 1

            encoded_word = encode(word)

            
            if HDC.compare(encoded_word, french) > HDC.compare(encoded_word, english):
                prediction = "french"
            else:
                prediction = "english"

            # If the prediction is correct, increment success count
            if prediction == "english":
                success_count += 1

            # If total_count reaches 1000, break the loop
            if total_count == 2000:
                break

    # Calculate success rate
    success_rate = success_count / total_count

    print(f"Success rate: {success_rate * 100}%")

encodeWord1 = encode('something')
encodeWord2 = encode('something')

print(HDC.cosine_similarity(encodeWord1, encodeWord2))
print(HDC.compare(encodeWord1, encodeWord2))
# while True:
#     user_input = input("Enter a word (or 'exit' to quit): ")
#     if user_input.lower() == 'exit':
#         break

#     encoded_input = encode(user_input)

#     if HDC.cosine_similarity(encoded_input, french) > HDC.cosine_similarity(encoded_input, english):
#         print("french")
#     else:
#         print("english")
    