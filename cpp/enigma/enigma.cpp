// Author: Louis Heery (lah119)


#include <iostream>
#include <fstream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <exception>
#include "errors.h"
#include "enigma.hpp"
#include "utilities.hpp"
#include <stdio.h>
#include <string.h>
using namespace std;


Enigma::Enigma(int numberOfArgs, char** inputFiles) {

  // Creates object instances of each part of Enigma machine
  plugboard = new Plugboard(inputFiles[1]);

  reflector = new Reflector(inputFiles[2]);

  numberOfRotors = numberOfArgs - 4;

  // Rotors stored in Linked List of Rotor Objects
  rotors = new Rotor*[numberOfRotors];

  for (int i = 0; i < numberOfRotors; i++) {
    rotors[i] = new Rotor(inputFiles[3+i], i + 1);
  }

  // Setup up starting position of each rotor
  setupRotorPos(inputFiles[numberOfArgs - 1]);
}

int Enigma::setupRotorPos(char* rotorPosFile) {

  ifstream infile;
  infile.open(rotorPosFile);

  // Check input file was sucessfully opened
  if(!infile.is_open())
  {
    cerr << "ERROR OPENING CONFIGURATION FILE named " << rotorPosFile << endl;
    throw ERROR_OPENING_CONFIGURATION_FILE;
  }

  int i = 0;
  int currentNumber;

  // Reads each Number in the Input File
  while (infile >> currentNumber) {

    // Assigns each Number as the Current Position Variable of each Rotor object
    if (i < numberOfRotors) {
      rotors[i]->setCurrentPositionOfRotor(currentNumber);
      i++;
    } else {
      break;
    }

  }

  // If Number of Input variables aren't equal to the number of Rotors
  if (i != numberOfRotors) {
    cerr << "No starting position for rotor " << i << " in rotor position file: " << rotorPosFile << endl;
    throw NO_ROTOR_STARTING_POSITION;
  }

  // Checks whether any of the Rotors Notches are setup to rotate an adjacent
  // rotor on the next rotation of the Enigma machine
  initialCheck();

  return 0;
}

char Enigma::decodeCharacter(char inputCharacter) {

  // Rotate Rightmost rotor of enigma machine by 1 turn (and any other rotors)
  // which are setup to rotate
  rotate();

  // Inputs 1 CHARACTER -> Convert to its Index Value in Alphabet
  int inputCharacterIndex = charToAlphabetIndex(inputCharacter);

  // Input Character goes through each part of Enigma machine
  // Each time the inputCharacterIndex value is updated accordingly
  inputCharacterIndex = plugboard->forward(inputCharacterIndex);

  // Goes through all of the Rotors in the machine in forwards direction
  for (int i = numberOfRotors - 1; i >= 0; i--) {
    inputCharacterIndex = rotors[i]->forward(inputCharacterIndex);
  }

  inputCharacterIndex = reflector->forward(inputCharacterIndex);

  // Goes through all of the Rotors in the machine in backwards direction
  for (int i = 0; i < numberOfRotors; i++) {
    inputCharacterIndex = rotors[i]->backward(inputCharacterIndex);
  }

  inputCharacterIndex = plugboard->forward(inputCharacterIndex);

  // Convert the Character Index value back to a Char value
  char outputCharacter = alphabetIndexToChar(inputCharacterIndex);

  return outputCharacter;

}

void Enigma::initialCheck() {
  // Cycles through each rotor in machine to check whether one of their Notches
  // will cause adjacent rotor to rotate on the next turn of the Enigma machine
  for (int i = 0; i < numberOfRotors; i++) {
    rotors[i]->checkRotorIsAtNotchPosition();
  }

}

void Enigma::rotate() {

  // Loops through each Rotor, starting with Rightmost Rotor
  // and moving leftwards
  for (int i = numberOfRotors - 1; i >= 0; i--) {

    // Rightmost Rotor always rotates by 1 position
    if (i == (numberOfRotors - 1)) {
      int currentPosition = rotors[i]->findCurrentPositionOfRotor();
      currentPosition++;
      rotors[i]->setCurrentPositionOfRotor(currentPosition);

      // After Position is updated, function checks whether one of this rotor's
      // notches is setup to rotate the adjacent rotor on its left side
      rotors[i]->checkRotorIsAtNotchPosition();

    } else {

      // If the previous rotor is setup to move, then this rotor will rotate
      if (rotors[i+1]->rotorSetupToMove == true) {
        int currentPosition = rotors[i]->findCurrentPositionOfRotor();
        currentPosition++;
        rotors[i]->setCurrentPositionOfRotor(currentPosition);

        // Set the previous rotor's setupToMove attribute to false
        rotors[i+1]->rotorSetupToMove = false;

        // Then checks if current rotor is setup to rotate the rotor on its left
        rotors[i]->checkRotorIsAtNotchPosition();

      }
    }

  }
}

Enigma::~Enigma()
{
    //delete []s;
}
