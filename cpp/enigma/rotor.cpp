// Author: Louis Heery (lah119)
// Last Updated: 9th November 2019

#include <iostream>
#include <fstream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <exception>
#include "rotor.hpp"
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
    return 11;
  }

  int i = 0;
  int j = 0;
  int currentNumber;
  bool hasBeenConnected[52]; // Remembers if a letter is already connected to another
  fill_n(hasBeenConnected, 52, false);

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

    // First 26 Input Numbers correspond to Rotor mapping
    if (i < 26) {

      // Checks that letter isn't being connected to multiple letters
      if (hasBeenConnected[i] == true) {
        cerr << "ERROR 9 : INVALID_ROTOR_MAPPING" << endl;
        return 9;
      } else {
        rotorConnections[i] = currentNumber;
        rotorConnections[i] = currentNumber;
        hasBeenConnected[i] = true;
      }

      i++;

    // Additional Input Numbers correspond to Rotor Notch locations
    } else {
      // Sets Rotor Notch location
      rotorNotches[j] = currentNumber;
      j++;
    }



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
