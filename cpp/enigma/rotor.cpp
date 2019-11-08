// Author: Louis Heery (lah119)
// Last Updated:

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

  rotorNumber = rotorNumberInput;

  ifstream infile;
  infile.open(rotorFile);

  int i = 0;
  int j = 0;
  int currentNumber;
  bool hasBeenConnected[52];
  fill_n(hasBeenConnected, 52, false);

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

    if (i < 26) {

      if (hasBeenConnected[i] == true) {
        //cout << i;
        cout << "ERROR 9 : INVALID_ROTOR_MAPPING" << endl;
        return 9;
      } else {
        //cout << currentNumber;
        rotorConnections[i] = currentNumber;
        rotorConnections[i] = currentNumber;
        hasBeenConnected[i] = true;
      }

      i++;
    } else {
      // ROTOR NOTCHES SETUP HERE
      rotorNotches[j] = currentNumber;
      j++;
    }



  }

  numberOfNotches = j;

  // SHOULD I CHECK THAT EXACTLY 26 PARAMETERS HAVE BEEN PASSED IN ???

  infile.close();


  return 0;

}

int Rotor::forward(int characterIndex) {

  //cout << " == " << characterIndex << " == " << endl;
  cout << "_________ROTOR__________" << endl;
  cout << "Character = " << alphabetIndexToChar(characterIndex) << endl;
  cout << "Current Rotor position = " << findCurrentPositionOfRotor();
  characterIndex = characterIndex + findCurrentPositionOfRotor();
  //cout << "CharacterIndex" << characterIndex << endl;
  if (characterIndex > 25) {
    characterIndex = characterIndex - 26;
  }

  if (characterIndex < 0) {
    characterIndex = characterIndex + 26;
  }

  characterIndex = rotorConnections[characterIndex];
  //cout << characterIndex << "-_-" << endl;

  characterIndex = characterIndex - findCurrentPositionOfRotor();

  if (characterIndex > 25) {
    characterIndex = characterIndex - 26;
  }

  if (characterIndex < 0) {
    characterIndex = characterIndex + 26;
  }

  cout << " == " << characterIndex << " == " << endl;
  cout << "_________ROTOR__________" << endl;
  return characterIndex;

}

int Rotor::backward(int characterIndex) {

  //cout << endl;
  //cout << "_________ROTOR__________" << endl;
  //cout << "@1 = " << characterIndex << endl;
  characterIndex = characterIndex + findCurrentPositionOfRotor();

  //cout << "@2 = " << characterIndex << endl;

  if (characterIndex > 25) {
    characterIndex = characterIndex - 26;
  }

  //cout << "@3 = " << characterIndex << endl;

  if (characterIndex < 0) {
    characterIndex = characterIndex + 26;
  }

  //cout << "@4 = " << characterIndex << endl;

  for (int r = 0; r < 26; r++) {
    //cout << endl << "-" << r <<  " @ "<< rotorConnections[r] << "-" << endl;
  }

  //characterIndex = rotorConnections[characterIndex];

  //
  for (int i = 0; i < 26; i++) {

    if (characterIndex == rotorConnections[i]) {
      //cout << "$$ " << i << "$$";
      characterIndex = i;
      break;
    }
  }

  //cout << "@5 = " << characterIndex << endl;

  characterIndex = characterIndex - findCurrentPositionOfRotor();

  //cout << "@6 = " << characterIndex << endl;

  if (characterIndex > 25) {
    characterIndex = characterIndex - 26;
  }

  //cout << "@7 = " << characterIndex << endl;

  if (characterIndex < 0) {
    characterIndex = characterIndex + 26;
  }

  //cout << "@8 = " << characterIndex << endl;
  //cout << "_________ROTOR__________" << endl;
  return characterIndex;

}

int Rotor::findCurrentPositionOfRotor() {
  return currentPositionOfRotor;
}

void Rotor::setCurrentPositionOfRotor(int position) {
  currentPositionOfRotor = position;
  return;
}

void Rotor::checkRotorIsAtNotchPosition() {

  // If the Rotor X = at position where
  for (int j = 0; j < numberOfNotches; j++) {
    if (currentPositionOfRotor == rotorNotches[j]) {
      rotorSetupToMove = true;
    }
  }

}
