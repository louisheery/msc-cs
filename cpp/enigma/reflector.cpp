// Author: Louis Heery (lah119)
// Last Updated:

#include <iostream>
#include <fstream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <exception>
#include "reflector.hpp"
#include "utilities.hpp"
using namespace std;

Reflector::Reflector(char* reflectorFile) {
  setupReflector(reflectorFile);
}


int Reflector::forward(int characterIndex) {

  //cout << " =R= " << characterIndex << " =R= " << endl;

  for (int i = 0; i < 26; i++) {
    //cout << characterIndex << "%" << reflectorConnections[i];
    if (characterIndex == reflectorConnections[i]) {
      // Sets characterIndex to its pair's character index value
      if (i%2 == 0) {
        characterIndex = reflectorConnections[i + 1];
        //cout << " ()() " << characterIndex << " ()() ";
        break;
      } else {
        characterIndex = reflectorConnections[i - 1];
        //cout << " (#)() " << characterIndex << " ()(#) ";
        break;
      }
    }
  }

  //cout << " =R= " << characterIndex << " =R= " << endl;

  return characterIndex;

}

int Reflector::setupReflector(char* reflectorFile) {

  ifstream infile;
  infile.open(reflectorFile);

  int i = 0;
  int currentNumber;
  int firstNumber;
  bool hasBeenConnected[26];
  fill_n(hasBeenConnected, 26, false);

  while (infile >> currentNumber) {

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
        cout << "ERROR 9 : INVALID_REFLECTOR_MAPPING" << endl;
        return 9;
      }
    }

    if (hasBeenConnected[i] == true) {
      cout << "ERROR 9 : INVALID_REFLECTOR_MAPPING" << endl;
      return 9;
    } else {
      reflectorConnections[i] = currentNumber;
      hasBeenConnected[i] = true;
    }

    i++;
  }

  if (i != 26) {
    cout << i << endl;
    cout << "ERROR 10 : INCORRECT_NUMBER_OF_REFLECTOR_PARAMETERS" << endl;
    return 10;
  }

  infile.close();

  return 0;

}
