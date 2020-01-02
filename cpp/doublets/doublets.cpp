#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <cctype>
#include <fstream>

using namespace std;

#include "dictionary.h"
#include "doublets.h"

/* You are pre-supplied with the functions below. Add your own 
   function definitions to the end of this file. */

/* Looks up a given word in the dictionary of approved words. 
   Returns true if the word is in the dictionary.
   Otherwise returns false. */

bool dictionary_search(const char *word) {
  static Dictionary dictionary("words.txt");
  return dictionary.search(word);
}

/* add your function definitions here */

bool valid_step(const char* current_word, const char* next_word) {

    // 1. Check that next_word is in dictionary
    if (dictionary_search(next_word) == false) {
        return false;
    }

    // 2. Check if current_word and next_word differ by only 1 letter
    int numberOfDifferentLetters = 0;

    for (int i = 0; next_word[i] != '\0'; i++) {
        if (current_word[i] != next_word[i]) {
            
            numberOfDifferentLetters++;
        }
    }

    if (numberOfDifferentLetters == 1) {
        return true;
    } else {
        return false;
    }

}

bool display_chain(const char* wheat_chain[], ostream& o) {

    int numberOfWordsInChain = 0;

    for (int i = 0; wheat_chain[i] != NULL; i++) {
        numberOfWordsInChain++;
    }

    for (int i = 0; wheat_chain[i] != NULL; i++) {
        
        if ((i == 0) || (i == (numberOfWordsInChain - 1))) {

            for (int j = 0; wheat_chain[i][j] != '\0'; j++) {
                o << wheat_chain[i][j];
            }

        } else {

            for (int j = 0; wheat_chain[i][j] != '\0'; j++)
            {
                o << (char) tolower(wheat_chain[i][j]);
            }
        }

        o << "\n";
    }

    return true;

}

bool valid_chain(const char* chain[]) {

    int numberOfWordsInChain = 0;

    for (int i = 0; chain[i] != NULL; i++) {

        numberOfWordsInChain++;

    }

    // Check no duplicates
    for (int a = 0; a < numberOfWordsInChain; a++) {

        for (int b = a + 1; b < numberOfWordsInChain; b++) {

            // For each pair of words
            // First assume words are the same, until proved otherwise
            //cout << "COMPARING-" << chain[a] << "-AND-" << chain[b] << endl;
            bool areWordsSame = true;

            // For each pair of letters in the two words being compared
            for (int letter = 0; chain[a][letter] != '\0'; letter++) {
                if (chain[a][letter] != chain[b][letter]) {
                    // areWordsSame = False if any pair of letters are different
                    areWordsSame = false;
                }
            }

            // If the 2 words are found to be the same -> return False
            if (areWordsSame == true) {
                return false;
            }
        }
    }

    // Check each Step is Valid
    for (int i = 0; i < numberOfWordsInChain - 1; i++) {

        if (!valid_step(chain[i], chain[i+1])) {
            //cout << "invalid step same" << endl;
            return false;
        }
    }

    return true;

}

bool find_chain(const char *start_word, const char *target_word, const char *answer_chain[], int steps) {

    bool success = searcher(start_word, target_word, answer_chain, steps, 0);

    if (success && valid_chain(answer_chain)) {
        return true;
    }

    return false;


}

bool searcher(const char *current_word, const char* target_word, const char* answer_chain[], int steps, int currentStep) {

    //cout << "**" << current_word << " at " << currentStep << " of " << steps << endl;
    answer_chain[currentStep] = current_word;

    // Checks if current_word == target_word
    int sizeOfWord = 0;
    for (int i = 0; current_word[i] != '\0'; i++) {
        sizeOfWord++;
    }

    bool isEqual = true;
    for (int i = 0; current_word[i] != '\0'; i++) {
        if ((char) toupper(current_word[i]) != (char) target_word[i]) {
            isEqual = false;
        }
    }
    if (isEqual == true) {
        //cout << "YES" << endl;
        //cout << "**" << current_word << " at " << currentStep << " as it equals " << target_word << endl;
        //answer_chain[currentStep + 1] = NULL;
        //cout << "SAVED FINAL WORD" << endl;
        return true;
    }

    //currentStep++;

    // Checks if there are still steps remaining
    if (currentStep >= steps)
    {
        //cout << "TOO MANY STEPS" << currentStep << "/" << steps << endl;
        return false;
    }

    // Cycle through all characters of the current word
    for (int currentPlace = 0; current_word[currentPlace] != '\0'; currentPlace++) {

        // Cycle through all possible letter changes
        for (int currentLetter = 0; currentLetter < 26; currentLetter++) {

            char currentLet = (char) (currentLetter + 65);

            int sizeOfWord = 0;

            for (int i = 0; current_word[i] != '\0'; i++)
            {
                sizeOfWord++;
            }

            char *next_word = new char[sizeOfWord + 1];

            strcpy(next_word, current_word); // but modifying 1 letter to equal currentLet;

            // change 1 letter in next_word
            next_word[currentPlace] = currentLet;

            if (valid_step(current_word, next_word)) {

                
                if (searcher(next_word, target_word, answer_chain, steps, currentStep + 1) == true) {
                    //cout << "IM HERE" << endl;
                    //cout << "*1*" << current_word << " at " << currentStep << endl;
                    //answer_chain[currentStep] = next_word;
                    return true;
                } else {
                    continue;
                }
                
            }
        }
    }
    return false;
}