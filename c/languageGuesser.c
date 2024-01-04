#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "hdcLib.c"

#define DIMENSION 10000
#define N 10000
#define MAX_WORD_LENGTH 100

BipolarVector vars[27]; // Assuming we have a bipolar vector for each letter and space

// run this code with
// > clang -std=c11 -Wall languageGuesser.c -o languageGuesser && ./languageGuesser





void encodeAlphabet() {
    // Generate HDV for each letter and space
    for (int i = 0; i < 27; i++) {
        vars[i] = createRandomBipolarVector();
    }

    // Save to file
    FILE *file = fopen("alphabet.txt", "w");
    if (file == NULL) {
        printf("Could not open file alphabet.txt\n");
        return;
    }
    for (int i = 0; i < 27; i++) {
        for (int j = 0; j < N; j++) {
            fprintf(file, "%d ", vars[i].vector[j]);
        }
        fprintf(file, "\n");
    }
    fclose(file);

    printf("Saved alphabet to alphabet.txt\n");
}

void loadAlphabet() {
    // Load from file
    FILE *file = fopen("alphabet.txt", "r");
    if (file == NULL) {
        printf("Could not open file alphabet.txt\n");
        return;
    }
    for (int i = 0; i < 27; i++) {
        for (int j = 0; j < N; j++) {
            fscanf(file, "%d", &vars[i].vector[j]);
        }
    }
    fclose(file);
}

BipolarVector encodeSample(const char *file_path) {
    loadAlphabet();

    BipolarVector language = createEmptyBipolarVector();

    FILE *file = fopen(file_path, "r");
    if (file == NULL) {
        printf("Could not open file %s\n", file_path);
        return language;
    }

    char word[MAX_WORD_LENGTH];
    while (fscanf(file, "%s", word) != EOF) {
        int word_length = strlen(word);
        for (int i = 0; i < word_length - 2; i++) {
            BipolarVector first = rotateBipolarVector(vars[word[i] - 'a'], 2);
            BipolarVector second = rotateBipolarVector(vars[word[i + 1] - 'a'], 1);
            BipolarVector third = vars[word[i + 2] - 'a'];

            BipolarVector trigramSum = bindBipolarVectors(bindBipolarVectors(first, second), third);

            language = bundleBipolarVectors(language, trigramSum);
        }
    }

    fclose(file);

    return language;
}

void saveBipolarVectorToFile(BipolarVector vector, const char *file_path) {
    FILE *file = fopen(file_path, "w");
    if (file == NULL) {
        printf("Could not open file %s\n", file_path);
        return;
    }

    for (int i = 0; i < DIMENSION; i++) {
        fprintf(file, "%d\n", vector.vector[i]);
    }

    fclose(file);
}

BipolarVector loadBipolarVectorFromFile(const char *file_path) {
    BipolarVector vector = createEmptyBipolarVector();

    FILE *file = fopen(file_path, "r");
    if (file == NULL) {
        printf("Could not open file %s\n", file_path);
        return vector;
    }

    for (int i = 0; i < DIMENSION; i++) {
        fscanf(file, "%d", &vector.vector[i]);
    }

    fclose(file);

    return vector;
}

int main() {
    srand(time(NULL));

    // saving the the languages

    // BipolarVector english = encodeSample("en.txt");
    // saveBipolarVectorToFile(english, "en_vec.txt");
    // BipolarVector french = encodeSample("fr.txt");
    // saveBipolarVectorToFile(french, "fr_vec.txt");
    
    BipolarVector english = loadBipolarVectorFromFile("en_vec.txt");
    BipolarVector french = loadBipolarVectorFromFile("fr_vec.txt");

    BipolarVector test = encodeSample("test.txt");

    double cosineSimilarityFR = cosineSimilarityBinary(test, french);
    double cosineSimilarityEN = cosineSimilarityBipolar(test, english);


    printf("Cosine similarity with French: %f\n", cosineSimilarityFR);
    printf("Cosine similarity with English: %f\n", cosineSimilarityEN);

    if (cosineSimilarityFR > cosineSimilarityEN) {
        printf("The text is in French\n");
    } else {
        printf("The text is in English\n");
    }

    // double hammingBipolarDistanceFR = hammingBipolarDistance(test, french);
    // double hammingBipolarDistanceEN = hammingBipolarDistance(test, english);

    // puts("");
    // printf("Hamming distance with French: %f\n", hammingBipolarDistanceFR);
    // printf("Hamming distance with English: %f\n", hammingBipolarDistanceEN);

    return 0;
}