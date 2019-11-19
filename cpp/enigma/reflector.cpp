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

  int i = 0; // Counts number of reflector input values that have been read
  int currentNumber; // Stores current integer being read in from setup file
  int firstNumber; // Stores first Letter in Pair of Connected letters being inputted
  bool hasBeenConnected[26]; // Remembers if a letter is already connected to another
  fill_n(hasBeenConnected, 26, false); // Fills hasBeenConnected array with 'false'

  // Create in file stream, and check file was opened correctly
  ifstream infilechecker;
  infilechecker.open(reflectorFile);

  // Loops through each input number to check for non-numeric characters
  while (!infilechecker.eof()) {

    // Removes any whitespace from file being read
    infilechecker >> ws;

    // Checks that end of file (EOF) has not been reached
    if (infilechecker.peek() == EOF) {
      break;
    }

    // Reads in first number from file
    infilechecker >> currentNumber;

    // Will Fail if the inputted is NOT an integer, since currentNumber = Int
    if(infilechecker.fail()){
      cerr << "Non-numeric character in reflector file " << reflectorFile << endl;
      throw NON_NUMERIC_CHARACTER;
    }
}
  infilechecker.close();

  // Create in file stream, and check file was opened correctly
  ifstream infile;
  infile.open(reflectorFile);

  if(!infile.is_open())
  {
    cerr << "Could not open reflector configuration file named: " << reflectorFile << endl;
    throw ERROR_OPENING_CONFIGURATION_FILE;
  }

  // Loops through each input number
  while (infile >> currentNumber) {

    // Checks that inputted value is in range of Alphabet index
    if (currentNumber < 0 || currentNumber > 25) {
      cerr << "Invalid reflector index character inputted of: " << currentNumber << endl;
      throw INVALID_INDEX;
    }

    // Checks that more than 26 parameters haven't been entered into reflector
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
      throw INCORRECT_NUMBER_OF_REFLECTOR_PARAMETERS;
    } else {
      reflectorConnections[i] = currentNumber;
      hasBeenConnected[i] = true;
    }

    i++;
  }

  // Checks that all letters in Reflector are connected to another
  if (i%2 != 0) {
    cerr << "Incorrect (odd) number of parameters in reflector file " << reflectorFile << endl;
    throw INCORRECT_NUMBER_OF_REFLECTOR_PARAMETERS;
  }

  // Checks that 26 characters have been read in from file.
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
