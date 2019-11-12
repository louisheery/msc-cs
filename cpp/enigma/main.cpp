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
using namespace std;


int main(int argc, char** argr) {

  // Minimum of 3 arguments are required to describe the simplest Enigma machine
  if (argc < 3) {
    cerr << "usage: enigma plugboard-file reflector-file (<rotor-file>)* rotor-positions" << endl;
    return INSUFFICIENT_NUMBER_OF_PARAMETERS;
  }

  // Define pointer to Enigma machine, and initiate Object
  Enigma *enigma;

  try {
    enigma = new Enigma(argc, argr);
  } catch (int error) {
    return error;
  }


  string inputString;
  cin >> inputString;
  int stringLength = (int) inputString.length();

  // Enigma Machine is inputted with each input character in turn
  // Output produced by enigma machine is then outputted to cout
  for (int i = 0; i < stringLength; i++) {
    int currentInputValue = static_cast<int>(inputString[i] - 'A');
      if (currentInputValue < 0 || currentInputValue >= 26) {
      	cerr << inputString[i] <<  " is not a valid input character (input characters must be upper case letters A-Z)!" << endl;
      	return INVALID_INPUT_CHARACTER;
      }
    char inputStringChar = (char) inputString[i];
    char outputStringChar = enigma->decodeCharacter(inputStringChar);
    cout << outputStringChar;
  }

  return NO_ERROR;

}
