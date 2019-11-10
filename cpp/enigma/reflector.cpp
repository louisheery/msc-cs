// Author: Louis Heery (lah119)
// Last Updated: 9th November 2019

#include <iostream>
#include <fstream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <exception>
#include "reflector.hpp"
#include "utilities.hpp"
using namespace std;


Reflector::Reflector(char* reflectorFile) {
  setupReflector(reflectorFile);
}

int Reflector::setupReflector(char* reflectorFile) {

  // Create in file stream, and check file was opened correctly
  ifstream infile;
  infile.open(reflectorFile);

  if(!infile.is_open())
  {
    cerr << "ERROR OPENING CONFIGURATION FILE named " << reflectorFile << endl;
    return 11;
  }

  int i = 0;
  int currentNumber;
  int firstNumber; // Stores first Letter in Pair of Connected letters being inputted
  bool hasBeenConnected[26]; // Remembers if a letter is already connected to another
  fill_n(hasBeenConnected, 26, false);

  // Loops through each input number
  while (infile >> currentNumber) {

    // Checks that inputted value is an integer
    if ((int) currentNumber != currentNumber) {
      cerr << "ERROR 2 : INVALID_INPUT_CHARACTER";
      return 2;
    }

    // Checks that inputted value is in range of Alphabet index
    if (currentNumber < 0 || currentNumber > 25) {
      cerr << "ERROR 3 : INVALID_INDEX" << endl;
      return 3;
    }

    // Checks a letter isn't being connected to itself by Reflector
    if (i%2 == 0) {
      firstNumber = currentNumber;
    } else {
      if (currentNumber == firstNumber) {
        cerr << "ERROR 9 : INVALID_REFLECTOR_MAPPING" << endl;
        return 9;
      }
    }

    // Checks that letter isn't being connected to multiple letters
    if (hasBeenConnected[i] == true) {
      cerr << "ERROR 9 : INVALID_REFLECTOR_MAPPING" << endl;
      return 9;
    } else {
      reflectorConnections[i] = currentNumber;
      hasBeenConnected[i] = true;
    }

    i++;
  }

  // Checks that all letters in Plugboard are connected to another
  if (i != 26) {
    cerr << "ERROR 10 : INCORRECT_NUMBER_OF_REFLECTOR_PARAMETERS" << endl;
    return 10;
  }

  infile.close();

  return 0;

}

int Reflector::forward(int characterIndex) {

  // Loops through each letter in the reflectorConnections array to find match
  for (int i = 0; i < 26; i++) {
    if (characterIndex == reflectorConnections[i]) {
      // Sets characterIndex to its pair's character index value
      if (i%2 == 0) {
        characterIndex = reflectorConnections[i + 1];
        break;
      } else {
        characterIndex = reflectorConnections[i - 1];
        break;
      }
    }
  }

  return characterIndex;

}
