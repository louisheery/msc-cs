// Author: Louis Heery (lah119)


#include <iostream>
#include <fstream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <exception>
#include "rotor.hpp"
#include "errors.h"
#include "utilities.hpp"
using namespace std;


Rotor::Rotor(char* rotorFile, int rotorNumberInput) {
  setupRotor(rotorFile, rotorNumberInput);
}

int Rotor::setupRotor(char* rotorFile, int rotorNumberInput) {

  // Sets rotorNumber attribute of Rotor Object
  rotorNumber = rotorNumberInput;

  // Create in file stream, and check file was opened correctly
  ifstream infile;
  infile.open(rotorFile);

  if(!infile.is_open())
  {
    cerr << "ERROR OPENING CONFIGURATION FILE named " << rotorFile << endl;
    throw ERROR_OPENING_CONFIGURATION_FILE;
  }

  int i = 0;
  int j = 0;
  int currentNumber;
  int hasBeenConnected[52]; // Remembers if a letter is already connected to another
  fill_n(hasBeenConnected, 52, -1);

  // Loops through each input number
  while (infile >> currentNumber) {

    // Checks that inputted value is an integer
    if ((int) currentNumber != currentNumber) {
      cerr << "Non-numeric character for mapping in rotor file " << rotorFile;
      throw INVALID_INPUT_CHARACTER;
    }

    // Checks that inputted value is in range of Alphabet index
    if (currentNumber < 0 || currentNumber > 25) {
      cerr << "ERROR 3 : INVALID_INDEX" << endl;
      throw INVALID_INDEX;
    }

    // First 26 Input Numbers correspond to Rotor mapping
    if (i < 26) {

      // Checks that letter isn't being connected to multiple letters
      if (hasBeenConnected[i] != -1) {
        cerr << "Invalid mapping of input " << currentNumber << " to output " << (i) << " (output " << i << " is already mapped to from input " << hasBeenConnected[i] << ") in rotor file " << rotorFile << endl;
        throw INVALID_ROTOR_MAPPING;
      } else {
        rotorConnections[i] = currentNumber;
        hasBeenConnected[i] = currentNumber;
      }

      i++;

    // Additional Input Numbers correspond to Rotor Notch locations
    } else {
      // Sets Rotor Notch location
      rotorNotches[j] = currentNumber;
      j++;
    }
  }

  if (i < 26) {
    cerr << "Not all inputs mapped in rotor file: " << rotorFile << endl;
    throw INVALID_ROTOR_MAPPING;
  }

  numberOfNotches = j;

  infile.close();


  return 0;

}

int Rotor::forward(int characterIndex) {

  // Adds current position of Rotor to get relative characterIndex position
  characterIndex = characterIndex + findCurrentPositionOfRotor();
  normaliseIndexPosition(characterIndex);

  // Obtains mapping of Rotor connection from the linked list
  characterIndex = rotorConnections[characterIndex];
  normaliseIndexPosition(characterIndex);

  // Subtracts current position of Rotor to get original characterIndex position
  characterIndex = characterIndex - findCurrentPositionOfRotor();
  normaliseIndexPosition(characterIndex); // Incase characterIndex > 25

  return characterIndex;

}

int Rotor::backward(int characterIndex) {

  // Adds current position of Rotor to get relative characterIndex position
  characterIndex = characterIndex + findCurrentPositionOfRotor();
  normaliseIndexPosition(characterIndex);

  // Loops through all 26 letters to find a match on the Rotor
  for (int i = 0; i < 26; i++) {

    // Checks if current letter is a match
    if (characterIndex == rotorConnections[i]) {
      characterIndex = i; // Reassigns value of characterIndex
      break;
    }
  }

  normaliseIndexPosition(characterIndex);

  characterIndex = characterIndex - findCurrentPositionOfRotor();
  normaliseIndexPosition(characterIndex);

  return characterIndex;

}

int Rotor::findCurrentPositionOfRotor() {
  return currentPositionOfRotor;
}

void Rotor::setCurrentPositionOfRotor(int position) {
  currentPositionOfRotor = position; // Allows manipulation of private attribute
  return;
}

void Rotor::checkRotorIsAtNotchPosition() {

  // Loops through each notch location
  // and checks if a notch is equal to current position of rotors
  // IF TRUE -> then rotor is setup to cause adjacent rotor to rotate on the
  //            next rotation of rotor
  for (int j = 0; j < numberOfNotches; j++) {
    normaliseIndexPosition(currentPositionOfRotor);
    if (currentPositionOfRotor == rotorNotches[j]) {
      rotorSetupToMove = true;
    }
  }

}
