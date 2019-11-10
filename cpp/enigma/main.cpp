// Author: Louis Heery (lah119)
// Last Updated: 9th November 2019

#include <iostream>
#include <fstream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <exception>
#include "enigma.hpp"
#include "utilities.hpp"
using namespace std;


int main(int argc, char** argr) {

  // Minimum of 3 arguments are required to describe the simplest Enigma machine
  if (argc < 3) {
    cerr << "ERROR 1 : INSUFFICIENT_NUMBER_OF_PARAMETERS";
    return 1;
  }

  // Define pointer to Enigma machine, and initiate Object
  Enigma *enigma;
  enigma = new Enigma(argc, argr);

  string inputString;
  cin >> inputString;
  int stringLength = (int) inputString.length();

  // Enigma Machine is inputted with each input character in turn
  // Output produced by enigma machine is then outputted to cout
  for (int i = 0; i < stringLength; i++) {
    char inputStringChar = (char) inputString[i];
    char outputStringChar = enigma->decodeCharacter(inputStringChar);
    cout << outputStringChar;
  }

  return 0;

}
