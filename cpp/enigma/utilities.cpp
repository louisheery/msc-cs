// Author: Louis Heery (lah119)
// Last Updated:

#include <iostream>
#include <fstream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <exception>
#include <map>
#include "utilities.hpp"
using namespace std;

/*
map<int, string> const errors = {
{INSUFFICIENT_NUMBER_OF_PARAMETERS, 1},
{INVALID_INPUT_CHARACTER, 2},
{INVALID_INDEX, 3},
{NON_NUMERIC_CHARACTER, 4},
{IMPOSSIBLE_PLUGBOARD_CONFIGURATION, 5},
{INCORRECT_NUMBER_OF_PLUGBOARD_PARAMETERS, 6},
{INVALID_ROTOR_MAPPING, 7},
{NO_ROTOR_STARTING_POSITION, 8},
{INVALID_REFLECTOR_MAPPING, 9},
{INCORRECT_NUMBER_OF_REFLECTOR_PARAMETERS, 10},
{ERROR_OPENING_CONFIGURATION_FILE, 11},
{NO_ERROR, 0}
};
*/


char alphabetIndexToChar(int index) {

  char characterEquivalent = (char) (index + 65);

  return characterEquivalent;

}

int charToAlphabetIndex(char character) {

  int indexEquivalent = ((int) character) - 65;

  return indexEquivalent;
}

/*
void check_error(int r) {
  throw std::runtime_error(errors.at(r));
}

*/
