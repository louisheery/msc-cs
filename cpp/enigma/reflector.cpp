// Author: Louis Heery (lah119)


#include <iostream>
#include <fstream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <exception>
#include "errors.h"
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
    throw ERROR_OPENING_CONFIGURATION_FILE;
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
      cerr << "Non-numeric character in reflector file " << reflectorFile;
      throw INVALID_INPUT_CHARACTER;
    }

    // Checks that inputted value is an integer
    if ((int) currentNumber != currentNumber) {
      cerr << "Non-numeric character in reflector file " << reflectorFile;
      throw INVALID_INPUT_CHARACTER;
    }

    // Checks that inputted value is in range of Alphabet index
    if (currentNumber < 0 || currentNumber > 25) {
      cerr << "ERROR 3 : INVALID_INDEX" << endl;
      throw INVALID_INDEX;
    }

    if (i > 26) {
      cerr << "Incorrect (odd) number of parameters in reflector file " << reflectorFile << endl;
      throw INCORRECT_NUMBER_OF_REFLECTOR_PARAMETERS;
    }

    // Checks a letter isn't being connected to itself by Reflector
    if (i%2 == 0) {
      firstNumber = currentNumber;
    } else {
      if (currentNumber == firstNumber) {
        cerr << "Incorrect (odd) number of parameters in reflector file " << reflectorFile << endl;
        throw INVALID_REFLECTOR_MAPPING;
      }
    }

    // Checks that letter isn't being connected to multiple letters
    if (hasBeenConnected[i] == true) {
      cerr << "Incorrect (odd) number of parameters in reflector file " << reflectorFile << endl;
      throw INVALID_REFLECTOR_MAPPING;
    } else {
      reflectorConnections[i] = currentNumber;
      hasBeenConnected[i] = true;
    }

    i++;
  }

  // Checks that all letters in Plugboard are connected to another
  if (i%2 != 0) {
    cerr << "Incorrect (odd) number of parameters in reflector file " << reflectorFile << endl;
    throw INCORRECT_NUMBER_OF_REFLECTOR_PARAMETERS;
  }

  if (i != 26) {
    cerr << "Insufficient number of mappings in reflector file: " << reflectorFile << endl;
    throw INCORRECT_NUMBER_OF_REFLECTOR_PARAMETERS;
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
