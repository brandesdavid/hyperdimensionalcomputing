#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <sys/stat.h> // for mkdir

#include "hdcLib.c"

#define DIMENSION 10000
#define N 10000
#define MAX_WORD_LENGTH 100

BipolarVector vars[27]; // Assuming we have a bipolar vector for each letter + space


void encodeAlphabet() {
    // Generate HDV for each letter and space
    for (int i = 0; i < 27; i++) {
        vars[i] = createRandomBipolarVector();
    }

    // Save to file
    FILE *file = fopen("./alphabet.txt", "w");
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
    FILE *file = fopen("./alphabet.txt", "r");
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
BipolarVector encodeSampleWords(const char *file_path, int max_words) {
    loadAlphabet();

    BipolarVector language = createEmptyBipolarVector();
    int word_count = 0;

    FILE *file = fopen(file_path, "r");
    if (file == NULL) {
        printf("Could not open file %s\n", file_path);
        return language;
    }

    char word[MAX_WORD_LENGTH];
    while (fscanf(file, "%s", word) != EOF && word_count < max_words) {
        int word_length = strlen(word);
        for (int i = 0; i < word_length - 2; i++) {
            BipolarVector first = rotateBipolarVector(vars[word[i] - 'a'], 3);
            BipolarVector second = rotateBipolarVector(vars[word[i + 1] - 'a'], 2);
            BipolarVector third = rotateBipolarVector(vars[word[i + 2] - 'a'], 1);

            BipolarVector trigramSum = bindBipolarVectors(bindBipolarVectors(first, second), third);

            language = bundleBipolarVectors(language, trigramSum);
        }
        word_count++;
    }

    fclose(file);

    return language;
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
        printf("Creating file %s\n", file_path);
        
        char dir_path[strlen(file_path) + 1];
        strncpy(dir_path, file_path, strrchr(file_path, '/') - file_path);
        dir_path[strrchr(file_path, '/') - file_path] = '\0';

        // Create directory
        mkdir(dir_path, 0777); // for Linux
        // _mkdir(dir_path); // for Windows

        // Try to open the file again with "a+" mode, which creates the file if it does not exist
        file = fopen(file_path, "a+");
        
        if (file == NULL) {
            printf("Could not create file %s\n", file_path);
            return;
        }
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