// Author: Louis Heery (lah119)

#include <iostream>
#include <fstream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <ctype.h>
#include "sstream"
#include <exception>
#include "errors.h"
#include "plugboard.hpp"
#include "utilities.hpp"
using namespace std;


Plugboard::Plugboard(char* plugboardFile) {
  setupPlugboard(plugboardFile);
}

void Plugboard::setupPlugboard(char* plugboardFile) {

  int i = 0;
  int currentNumber; // Stores current integer being read in from setup file
  int firstNumber; // Stores first Letter in Pair of Connected letters being inputted
  bool hasBeenConnected[26]; // Remembers if a letter is already connected to another
  fill_n(hasBeenConnected, 26, false);

  // Create in file stream, and check file was opened correctly
  ifstream infilechecker;
  infilechecker.open(plugboardFile);

  // Loops through each input number to check for non-numeric characters
  while (!infilechecker.eof()) {

    // Removes any whitespace from input file.
    infilechecker >> ws;

    if (infilechecker.peek() == EOF) {
      break;
    }

    infilechecker >> currentNumber;

    // Will fail if inputted value is not an integer
    if(infilechecker.fail()){
      cerr << "Non-numeric character in plugboard file " << plugboardFile << endl;
      throw NON_NUMERIC_CHARACTER;
    }

}
  infilechecker.close();

  // Create in file stream
  ifstream infile;
  infile.open(plugboardFile);

  if(!infile.is_open())
  {
    cerr << "Could not open plugboard configuration file named: " << plugboardFile << endl;
    throw ERROR_OPENING_CONFIGURATION_FILE;
  }


  while (infile >> currentNumber) {

    // Checks that inputted value is in range of Alphabet index
    if (currentNumber < 0 || currentNumber > 25) {
      cerr << "Plugboard configuration file " << plugboardFile << " contains a non-alphabet character" << endl;
      throw INVALID_INDEX;
    }

    // Checks a letter isn't being connected to itself by Plugboard
    if (i%2 == 0) {
      firstNumber = currentNumber;
    } else {
      if (currentNumber == firstNumber) {
        cerr << "Plugboard file named " << plugboardFile << " tried to connect a letter (index = " << firstNumber << ") to itself" << endl;
        throw IMPOSSIBLE_PLUGBOARD_CONFIGURATION;
      }
    }

    // Checks that letter isn't being connected to multiple letters
    if (hasBeenConnected[i] == true) {
      cerr << "Incorrect number of parameters in plugboard file " << plugboardFile << endl;
      throw INCORRECT_NUMBER_OF_PLUGBOARD_PARAMETERS;
    } else {
      plugboardConnections[i] = currentNumber;
      hasBeenConnected[i] = true;
    }
    i++;
  }

  // Check correct number of plugboard parameters have been entered
  if (i > 26) {
    cerr << "Incorrect number of parameters in plugboard file " << plugboardFile << endl;
    throw INCORRECT_NUMBER_OF_PLUGBOARD_PARAMETERS;
  }

  if (i%2 == 1) {
    cerr << "Incorrect number of parameters in plugboard file " << plugboardFile << endl;
    throw INCORRECT_NUMBER_OF_PLUGBOARD_PARAMETERS;
  }

  // Sets the total number of Connectioned Letters made (each connection counts as 2 contacts)
  numberOfConnectionedLetters = i;

  infile.close();

}


int Plugboard::forward(int characterIndex) {

  // Loops through each Letter stored in the Plugboard Connections List
  for (int i = 0; i < numberOfConnectionedLetters; i++) {

    if (characterIndex == plugboardConnections[i]) {
      // Changes characterIndex to characterIndex of the letter it is connected to
      if (i%2 == 0) {
        characterIndex = plugboardConnections[i + 1];
        break;
      } else {
        characterIndex = plugboardConnections[i - 1];
        break;
      }
    }
  }
  return characterIndex;

}
