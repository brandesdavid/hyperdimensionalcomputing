from hdcPY import HDC
import numpy as np

N = 10000


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
            word = line.strip().replace(' ', '')
        
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
    lang = encodeFile(path=path, num_lines=10000)
    np.savetxt('vec_'+path, lang, fmt='%d')

def loadLang(path='words_vec.txt'):
    return np.loadtxt(path, dtype=int)


encodeSaveLang('en.txt')



def success_rate(totals=2000):
    # ---- testing ----
    compare_values = []

    total_count = 0
    # Open the file
    with open('english_words.txt', 'r') as file:
        # Iterate over each line in the file
        for line in file:
            word = line.strip()

            total_count += 1

            encoded_word = encode(word)

            
            compare_value = HDC.compare(encoded_word, english)
            compare_values.append(compare_value)

            if compare_value > 5000:
                prediction = "english"
            else:
                prediction = "false"

            # If the prediction is correct, increment success count
            if prediction == "english":
                success_count += 1

            # If total_count reaches 1000, break the loop
            if total_count == totals:
                break

    median_compare_value = np.median(compare_values)
    print(f"Median HDC.compare value: {median_compare_value}")

# success_rate(10000)

# while True:
#     user_input = input("Enter a word (or 'exit' to quit): ")
#     if user_input.lower() == 'exit':
#         break

#     encoded_input = encode(user_input)

#     print(HDC.compare(encoded_input, english))
    