// Author: Louis Heery (lah119)
// Last Updated:

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

  ifstream infile;
  infile.open(plugboardFile);

  int i = 0;
  int currentNumber;
  bool isInMiddleOfRow = true;
  int firstNumber;
  bool hasBeenConnected[26];
  fill_n(hasBeenConnected, 26, false);

  while (infile >> currentNumber) {

    // NEED TO FIND A WAY TO CHECK IF A CHARACTER WAS INPUTTED
    if (/*(currentNumber == NULL) || */ ((int) currentNumber != currentNumber)) {
      cout << "ERROR 2 : INVALID_INPUT_CHARACTER";
      return 2;
    }

    if (currentNumber < 0 || currentNumber > 25) {
      cout << "ERROR 3 : INVALID_INDEX" << endl;
      return 3;
    }

    if (i%2 == 0) {
      firstNumber = currentNumber;
    } else {
      if (currentNumber == firstNumber) {
        cout << "ERROR 5 : IMPOSSIBLE_PLUGBOARD_CONFIGURATION" << endl;
        return 5;
      }
    }

    if (hasBeenConnected[i] == true) {
      cout << "ERROR 5 : IMPOSSIBLE_PLUGBOARD_CONFIGURATION" << endl;
      return 5;
    } else {
      plugboardConnections[i] = currentNumber;
      hasBeenConnected[i] = true;
    }
    i++;
  }

  if (i%2 > 0) {
    cout << "ERROR 6 : INCORRECT_NUMBER_OF_PLUGBOARD_PARAMETERS" << endl;
    return 6;
  }

  numberOfConnectionedLetters = i;  // sets the total number of Connectioned Letters made (each connection counts as 2 contacts)

  infile.close();

  return 0;

}


int Plugboard::forward(int characterIndex) {

  //cout << " == " << characterIndex << " == " << endl;

  for (int i = 0; i < numberOfConnectionedLetters; i++) {

    if (characterIndex == plugboardConnections[i]) {
      //cout << "ITS from " << i << " " << (i%2) << characterIndex << " to " << plugboardConnections[i];
      // Sets characterIndex to its pair's character index value
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

int Plugboard::backward(int characterIndex) {

  //cout << " =!= " << characterIndex << " =!= " << endl;

  for (int i = 0; i < numberOfConnectionedLetters; i++) {

    if (characterIndex == plugboardConnections[i]) {
      //cout << "ITS from " << i << " " << (i%2) << characterIndex << " to " << plugboardConnections[i];
      // Sets characterIndex to its pair's character index value
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
