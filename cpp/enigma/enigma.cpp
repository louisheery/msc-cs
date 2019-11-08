// Author: Louis Heery (lah119)
// Last Updated:

#include <iostream>
#include <fstream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <exception>
#include "enigma.hpp"
#include "utilities.hpp"
#include <stdio.h>
#include <string.h>
using namespace std;


Enigma::Enigma(int numberOfArgs, char** inputFiles) {

  plugboard = new Plugboard(inputFiles[1]);

  reflector = new Reflector(inputFiles[2]);

  numberOfRotors = numberOfArgs - 4;

  rotors = new Rotor*[numberOfRotors];

  for (int i = 0; i < numberOfRotors; i++) {
    rotors[i] = new Rotor(inputFiles[3+i], i + 1);
  }

  setupRotorPos(inputFiles[numberOfArgs - 1]);
}




int Enigma::setupRotorPos(char* rotorPosFile) {

  ifstream infile;
  infile.open(rotorPosFile);

  int i = 0;
  int currentNumber;

  while (infile >> currentNumber) {

    if (i < numberOfRotors) {
      cout << "()()()" << currentNumber << "()()()" << endl;
      rotors[i]->setCurrentPositionOfRotor(currentNumber);
      i++;
    } else {
      break;
    }

  }

  if (i + 1 != numberOfRotors) {
    //cout << "ERROR 8 : NO_ROTOR_STARTING_POSITION";
    return 8;
  }

  return 0;
}

char Enigma::decodeCharacter(char inputCharacter) {

  // Rotate the Rotors of the Enigma machine by 1 turn
  rotate();

  cout << endl;
  cout << "---------------" << endl;
  // Inputs 1 CHARACTER -> Convert to its Index Value in Alphabet
  int inputCharacterIndex = charToAlphabetIndex(inputCharacter);
  cout << "Input = " << alphabetIndexToChar(inputCharacterIndex) << inputCharacterIndex << endl;

  // Goes through enigma machine process, accessing the rotors, reflectors and plugboardFile

  // Goes through the Plugboard forwards
  inputCharacterIndex = plugboard->forward(inputCharacterIndex);
  cout << "After Plugboard = " << alphabetIndexToChar(inputCharacterIndex) << inputCharacterIndex << endl;


  // Goes through all of the Rotors in the machine forwards
  for (int i = 0; i < numberOfRotors; i++) {
    inputCharacterIndex = rotors[i]->forward(inputCharacterIndex);
    cout << "After Rotor = " << alphabetIndexToChar(inputCharacterIndex) << inputCharacterIndex  << endl;
  }


  // Goes through the Reflector
  inputCharacterIndex = reflector->forward(inputCharacterIndex);
  cout << "After Reflector = " << alphabetIndexToChar(inputCharacterIndex) << inputCharacterIndex << endl;

  // Goes through all of the Rotors in the machine backwards
  for (int i = numberOfRotors - 1; i >= 0; i--) {
    inputCharacterIndex = rotors[i]->backward(inputCharacterIndex);
  }
  cout << "After Rotor backwards = " << alphabetIndexToChar(inputCharacterIndex) << inputCharacterIndex << endl;

  // Goes through the Plugboard backwards
  inputCharacterIndex = plugboard->backward(inputCharacterIndex);
  cout << "After Plugboard Backwards = " << alphabetIndexToChar(inputCharacterIndex) << inputCharacterIndex << endl;
  cout << "---------------" << endl;
  // Convert the Character Index value back to a Char value
  char outputCharacter = alphabetIndexToChar(inputCharacterIndex);



  // Outputs 1 CHARACTER
  return outputCharacter;

}


void Enigma::rotate() {

  for (int i = 0; i < numberOfRotors; i++) {

    rotors[i]->checkRotorIsAtNotchPosition();

    // Rotor 1 always rotates by 1 position
    if (i == 0) {
      int currentPosition = rotors[i]->findCurrentPositionOfRotor();
      currentPosition++;
      rotors[i]->setCurrentPositionOfRotor(currentPosition);

    // Check whether any other rotor should be rotated:
    // Only apply if rotor != the first rotor
    } else {

      // If the previous rotor (e.g. rotor 1) is setup to move -> then move this rotor (e.g. rotor 2)
      if (rotors[i-1]->rotorSetupToMove == true) {
        int currentPosition = rotors[i]->findCurrentPositionOfRotor();
        currentPosition++;
        rotors[i]->setCurrentPositionOfRotor(currentPosition);

        // Set the rotorSetupToMove back to false
        rotors[i-1]->rotorSetupToMove = false;
      }
    }

    rotors[i]->checkRotorIsAtNotchPosition();

  }
}
