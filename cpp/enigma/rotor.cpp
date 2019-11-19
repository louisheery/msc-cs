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

  // Initialise temporary variables
  int i = 0;
  int j = 0;
  int currentNumber; // Stores current integer being read in from setup file

  // Fill hasBeenConnected Array with -1 values
  // (-1 represents that a rotor contact hasn't been connected)
  for (int k = 0; k < 52; k++) {
   hasBeenConnected[k] = -1;
  }

  // STEP 1: Checks that file doesn't contain non-numeric characters
  // Create in file stream
  ifstream infilechecker;
  infilechecker.open(rotorFile);

  // Loops through each input number to check for non-numeric characters
  while (!infilechecker.eof()) {

    infilechecker >> ws;

    if (infilechecker.peek() == EOF) {
      break;
    }

    infilechecker >> currentNumber;

    // If ifstream reads a non-integer value, the following statement = true
    if(infilechecker.fail()){
      cerr << "Non-numeric character for mapping in rotor file " << rotorFile << endl;
      throw NON_NUMERIC_CHARACTER;
    }
  }
  infilechecker.close();

  // STEP 2: Read in the Rotor setup file and setup Rotor
  // Create in file stream, and check file was opened correctly
  ifstream infile;
  infile.open(rotorFile);

  // Checks configuration file was opened correctly
  if(!infile.is_open())
  {
    cerr << "Could not open rotor configuration file named: " << rotorFile << endl;
    throw ERROR_OPENING_CONFIGURATION_FILE;
  }

  // Loops through each Integer in Rotor File
  while (infile >> currentNumber) {

    // Checks that inputted value is an integer
    if ((int) currentNumber != currentNumber) {
      cerr << "Non-numeric character for mapping in rotor file " << rotorFile;
      throw INVALID_INPUT_CHARACTER;
    }

    // Checks that inputted value is in range of Alphabet index
    if (currentNumber < 0 || currentNumber > 25) {
      cerr << "Invalid rotor index character inputted of: " << currentNumber << endl;
      throw INVALID_INDEX;
    }

    // First 26 Input Numbers correspond to Rotor mapping
    if (i < 26) {
      // Checks that letter isn't being connected to multiple letters

      for (int l = 0; l < i; l++) {
        if (hasBeenConnected[l] == currentNumber) {
          cerr << "Invalid mapping of input " << i << " to output ";
          cerr << (currentNumber) << " (output " << currentNumber;
          cerr << " is already mapped to from input " << l;
          cerr << ") in rotor file: " << rotorFile << endl;
          throw INVALID_ROTOR_MAPPING;
        }
      }
      hasBeenConnected[i] = currentNumber;
      rotorConnections[i] = currentNumber;
      i++;

    // Additional Input Numbers correspond to Rotor Notch locations
    } else {
      // Sets Rotor Notch location
      rotorNotches[j] = currentNumber;
      j++;
    }
  }

  // Checks whether all inputs are mapped
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

  // Index Position is normalised after each change is applied
  normaliseIndexPosition(characterIndex);

  // Remove the relative Rotor positioning
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
