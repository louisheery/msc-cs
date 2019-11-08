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

using namespace std;


int main(int argc, char** argr) {

  if (argc < 3) {
    cout << "ERROR 1 : INSUFFICIENT_NUMBER_OF_PARAMETERS";
    return 1;
  }

  Enigma *enigma;

  enigma = new Enigma(argc, argr);

  cout << "Enter a string to encode: " << endl;

  std::string inputString;
  cin >> inputString;

  int stringLength = (int) inputString.length();
  for (int i = 0; i < stringLength; i++) {
    char inputStringChar = (char) inputString[i];
    char outputStringChar = enigma->decodeCharacter(inputStringChar);
    cout << outputStringChar;
  }

  return 0;

}
