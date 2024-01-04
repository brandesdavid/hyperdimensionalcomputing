#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include "hdc.h"

#define DIMENSION 10000

// run this code with
// > clang -std=c11 -Wall hdcLib.c -o hdcLib && ./hdcLib


// -- binary vectors --

BinaryVector createRandomBinaryVector() {
    BinaryVector bv;
    for (int i = 0; i < DIMENSION; i++) {
        bv.vector[i] = rand() % 2;
    }
    return bv;
}

BinaryVector bindBinaryVectors(BinaryVector a, BinaryVector b) {
    BinaryVector result;
    for (int i = 0; i < DIMENSION; i++) {
        result.vector[i] = a.vector[i] ^ b.vector[i]; // XOR as a binding operation
    }
    return result;
}

BinaryVector bundleBinaryVectors(BinaryVector a, BinaryVector b) {
    BinaryVector result;
    for (int i = 0; i < DIMENSION; i++) {
        result.vector[i] = a.vector[i] | b.vector[i]; // OR as a bundling operation
    }
    return result;
}

BinaryVector rotateBinaryVector(BinaryVector a, int shift) {
    BinaryVector result;
    for (int i = 0; i < DIMENSION; i++) {
        result.vector[i] = a.vector[(i + shift) % DIMENSION];
    }
    return result;
}

// -- bipolar vectors --

BipolarVector createRandomBipolarVector() {
    BipolarVector bv;
    for (int i = 0; i < DIMENSION; i++) {
        bv.vector[i] = (rand() % 2) * 2 - 1; // Generates -1 or 1
    }
    return bv;
}

BipolarVector bindBipolarVectors(BipolarVector a, BipolarVector b) {
    BipolarVector result;
    for (int i = 0; i < DIMENSION; i++) {
        result.vector[i] = a.vector[i] * b.vector[i]; // Multiplication as a binding operation
    }
    return result;
}

BipolarVector bundleBipolarVectors(BipolarVector a, BipolarVector b) {
    BipolarVector result;
    for (int i = 0; i < DIMENSION; i++) {
        result.vector[i] = a.vector[i] + b.vector[i];
        if (result.vector[i] > 1) {
            result.vector[i] = 1;
        } else if (result.vector[i] < -1) {
            result.vector[i] = -1;
        }
    }
    return result;
}


BipolarVector rotateBipolarVector(BipolarVector a, int shift) {
    BipolarVector result;
    for (int i = 0; i < DIMENSION; i++) {
        result.vector[(i + shift) % DIMENSION] = a.vector[i];
    }
    return result;
}

BipolarVector createEmptyBipolarVector() {

    BipolarVector result;
    for (int i = 0; i < DIMENSION; i++) {
        result.vector[i] = 0;
    }
    return result;
}

int hammingBipolarDistance(BipolarVector a, BipolarVector b) {
    int distance = 0;
    for (int i = 0; i < DIMENSION; i++) {
        if (a.vector[i] != b.vector[i]) {
            distance++;
        }
    }
    return distance;
}

int hammingBinaryDistance(BinaryVector a, BinaryVector b) {
    int distance = 0;
    for (int i = 0; i < DIMENSION; i++) {
        if (a.vector[i] != b.vector[i]) {
            distance++;
        }
    }
    return distance;
}

// -- HDC --

double cosineSimilarityBipolar(BipolarVector a, BipolarVector b) {
    double dotProduct = 0.0;
    double magnitudeA = 0.0;
    double magnitudeB = 0.0;

    for (int i = 0; i < DIMENSION; i++) {
        dotProduct += a.vector[i] * b.vector[i];
        magnitudeA += a.vector[i] * a.vector[i];
        magnitudeB += b.vector[i] * b.vector[i];
    }

    magnitudeA = sqrt(magnitudeA);
    magnitudeB = sqrt(magnitudeB);

    if (magnitudeA == 0.0 || magnitudeB == 0.0) {
        // The cosine similarity is not defined if either magnitude is zero.
        return 0.0;
    }

    return dotProduct / (magnitudeA * magnitudeB);
}

double cosineSimilarityBinary(BipolarVector a, BipolarVector b) {
    int intersection = 0;
    int unionAB = 0;

    for (int i = 0; i < DIMENSION; i++) {
        if (a.vector[i] == 1 && b.vector[i] == 1) {
            intersection++;
        }
        if (a.vector[i] == 1 || b.vector[i] == 1) {
            unionAB++;
        }
    }

    if (unionAB == 0) {
        // The cosine similarity is not defined if the union is empty.
        return 0.0;
    }

    return (double)intersection / unionAB;
}