#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "languageEncoder.c"

// run this code with
// > clang -std=c11 -Wall languageGuesser.c -o languageGuesser && ./languageGuesser


int main() {
    srand(time(NULL));
    
    BipolarVector english_encoded = encodeSample("./training/eng.txt");
    saveBipolarVectorToFile(english_encoded, "./encoded/english.txt");

    BipolarVector deutsch_encoded = encodeSample("./training/deu.txt");
    saveBipolarVectorToFile(deutsch_encoded, "./encoded/deutsch.txt");

    BipolarVector italian_encoded  = encodeSample("./training/ita.txt");
    saveBipolarVectorToFile(italian_encoded , "./encoded/italian.txt");

    BipolarVector french_encoded  = encodeSample("./training/fra.txt");
    saveBipolarVectorToFile(french_encoded , "./encoded/french.txt");


    BipolarVector english_test_encoded = encodeSample("./testing/eng.txt");
    saveBipolarVectorToFile(english_test_encoded, "./test_encoded/eng.txt");

    BipolarVector deutsch_test_encoded = encodeSample("./testing/deu.txt");
    saveBipolarVectorToFile(deutsch_test_encoded, "./test_encoded/deu.txt");

    BipolarVector italian_test_encoded  = encodeSample("./testing/ita.txt");
    saveBipolarVectorToFile(italian_test_encoded , "./test_encoded/ita.txt");

    BipolarVector french_test_encoded  = encodeSample("./testing/fra.txt");
    saveBipolarVectorToFile(french_test_encoded , "./test_encoded/fra.txt");

    BipolarVector english = loadBipolarVectorFromFile("./encoded/english.txt");
    BipolarVector deutsch = loadBipolarVectorFromFile("./encoded/deutsch.txt");
    BipolarVector italian = loadBipolarVectorFromFile("./encoded/italian.txt");
    BipolarVector french = loadBipolarVectorFromFile("./encoded/french.txt");

    BipolarVector english_test = loadBipolarVectorFromFile("./test_encoded/eng.txt");
    BipolarVector deutsch_test = loadBipolarVectorFromFile("./test_encoded/deu.txt");
    BipolarVector italian_test = loadBipolarVectorFromFile("./test_encoded/ita.txt");
    BipolarVector french_test = loadBipolarVectorFromFile("./test_encoded/fra.txt");

   
    double similarityEN = cosineSimilarityBipolar(english_test, english);
    double similarityDE = cosineSimilarityBipolar(deutsch_test, deutsch);
    double similarityENDE = cosineSimilarityBipolar(english_test, deutsch);
    double similarityIT = cosineSimilarityBipolar(italian_test, italian);
    double similarityFR = cosineSimilarityBipolar(french_test, french);
    double similarityITFR = cosineSimilarityBipolar(italian_test, french);

    double similarityENIT = cosineSimilarityBipolar(english_test, italian);
    double similarityENFR = cosineSimilarityBipolar(english_test, french);
    double similarityDEIT = cosineSimilarityBipolar(deutsch_test, italian);
    double similarityDEFR = cosineSimilarityBipolar(deutsch_test, french);


    printf("en - en:  %f \n", similarityEN);
    printf("en - it:  %f \n", similarityENIT);
    printf("en - fr:  %f \n", similarityENFR);
    printf("en - de:  %f \n", similarityENDE);

    printf("de - de:  %f \n", similarityDE);
    printf("de - it:  %f \n", similarityDEIT);
    printf("de - fr:  %f \n", similarityDEFR);

    printf("it - it:  %f \n", similarityIT);
    printf("it - fr:  %f \n", similarityITFR);
     printf("fr - fr:  %f \n", similarityFR);


   
   
    




    return 0;
}