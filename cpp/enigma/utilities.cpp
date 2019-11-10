// Author: Louis Heery (lah119)
// Last Updated: 9th November 2019

#include <iostream>
#include <fstream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <exception>
#include <map>
#include "utilities.hpp"
using namespace std;


void normaliseIndexPosition(int &indexPosition) {

  // Reduces indexPosition by 26 if it is > 25
  while (indexPosition > 25) {
    indexPosition -= 26;
  }

  // Increases indexPosition by 26 if it is < 0
  while (indexPosition < 0) {
    indexPosition += 26;
  }

}


char alphabetIndexToChar(int index) {

  char characterEquivalent = (char) (index + 65);
  return characterEquivalent;

}

int charToAlphabetIndex(char character) {

  int indexEquivalent = ((int) character) - 65;
  return indexEquivalent;
}
