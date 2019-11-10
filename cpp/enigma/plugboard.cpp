// Author: Louis Heery (lah119)
// Last Updated: 9th November 2019

#include <iostream>
#include <fstream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <exception>
#include "plugboard.hpp"
#include "utilities.hpp"
using namespace std;


Plugboard::Plugboard(char* plugboardFile) {
  setupPlugboard(plugboardFile);
}

int Plugboard::setupPlugboard(char* plugboardFile) {

  // Create in file stream, and check file was opened correctly
  ifstream infile;
  infile.open(plugboardFile);

  if(!infile.is_open())
  {
    cerr << "ERROR OPENING CONFIGURATION FILE named " << plugboardFile << endl;
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

    // Checks a letter isn't being connected to itself by Plugboard
    if (i%2 == 0) {
      firstNumber = currentNumber;
    } else {
      if (currentNumber == firstNumber) {
        cerr << "ERROR 5 : IMPOSSIBLE_PLUGBOARD_CONFIGURATION" << endl;
        return 5;
      }
    }

    // Checks that letter isn't being connected to multiple letters
    if (hasBeenConnected[i] == true) {
      cerr << "ERROR 5 : IMPOSSIBLE_PLUGBOARD_CONFIGURATION" << endl;
      return 5;
    } else {
      plugboardConnections[i] = currentNumber;
      hasBeenConnected[i] = true;
    }
    i++;
  }

  // Checks if an even number of Index parameters were inputted
  if (i%2 > 0) {
    cerr << "ERROR 6 : INCORRECT_NUMBER_OF_PLUGBOARD_PARAMETERS" << endl;
    return 6;
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
