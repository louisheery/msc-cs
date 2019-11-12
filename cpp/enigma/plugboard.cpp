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

int Plugboard::setupPlugboard(char* plugboardFile) {

  int i = 0;
  int currentNumber;
  //int currentNumberOriginal;
  int firstNumber; // Stores first Letter in Pair of Connected letters being inputted
  bool hasBeenConnected[26]; // Remembers if a letter is already connected to another
  fill_n(hasBeenConnected, 26, false);

  // Create in file stream, and check file was opened correctly
  ifstream infile;
  infile.open(plugboardFile);
  if (infile.fail())
  {
    cerr << "ERROR OPENING CONFIGURATION FILE named " << plugboardFile << endl;
    throw ERROR_OPENING_CONFIGURATION_FILE;
  }

/*
  while (!infile.eof()) {

    infile >> currentNumberOriginal;

    if (infile.peek() == EOF) {
      cout << "@";
      break;
    }

    infile >> currentNumber;

    if (infile.fail()) {
      cerr << "ERROR 4 : NON_NUMERIC_CHARACTER";
      throw NON_NUMERIC_CHARACTER;
    }

    if (currentNumber < 0 || currentNumber >= 26) {
      cerr << "Plugboard configuration file " << plugboardFile << " contains a number not in the alphabet " << currentNumber << ". Exiting..." << endl;
      throw INVALID_INDEX;
    }

  }

  infile.close();

  infile.open(plugboardFile);

*/

  // Loops through each input number
  /*
  while (!infile.eof()) {

    if (infile.peek() == EOF) {
      break;
    }

    infile >> currentNumber;
*/

  while (infile >> currentNumber) {

    // Checks that inputted value is an integer
    if ((int) currentNumber != currentNumber) {
      cerr << "Non-numeric character in plugboard file " << plugboardFile;
      throw INVALID_INPUT_CHARACTER;
    }

    // Checks that inputted value is in range of Alphabet index
    if (currentNumber < 0 || currentNumber > 25) {
      cerr << "ERROR 3 : INVALID_INDEX" << endl;
      throw INVALID_INDEX;
    }

    // Checks a letter isn't being connected to itself by Plugboard
    if (i%2 == 0) {
      firstNumber = currentNumber;
    } else {
      if (currentNumber == firstNumber) {
        cerr << "Incorrect number of parameters in plugboard file " << plugboardFile << endl;
        throw IMPOSSIBLE_PLUGBOARD_CONFIGURATION;
      }
    }

    // Checks that letter isn't being connected to multiple letters
    if (hasBeenConnected[i] == true) {
      cerr << "Incorrect number of parameters in plugboard file " << plugboardFile << endl;
      throw IMPOSSIBLE_PLUGBOARD_CONFIGURATION;
    } else {
      plugboardConnections[i] = currentNumber;
      hasBeenConnected[i] = true;
    }
    i++;
  }

  if (i > 26) {
    cerr << "Incorrect (odd) number of parameters in plugboard file " << plugboardFile << endl;
    throw INCORRECT_NUMBER_OF_REFLECTOR_PARAMETERS;
  }

  // Checks if an even number of Index parameters were inputted
  if (i%2 > 0) {
    cerr << "Incorrect number of parameters in plugboard file " << plugboardFile << endl;
    throw INCORRECT_NUMBER_OF_PLUGBOARD_PARAMETERS;
  }

  // sets the total number of Connectioned Letters made (each connection counts as 2 contacts)
  numberOfConnectionedLetters = i;

  infile.close();

  return 0;

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
