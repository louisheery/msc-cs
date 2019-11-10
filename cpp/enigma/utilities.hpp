// Author: Louis Heery (lah119)
// Last Updated: 9th November 2019

#include <string>
#include <functional>
#include <map>
#include <iostream>


// Function converts a value corresponding to the index of a letter in the
// Alphabet of range 0-25 inclusive to its Corresponding Character Value (A-Z)
char alphabetIndexToChar(int index);

// Function converts a Character Value (A-Z) to the index of a letter in the
// Alphabet of range 0-25 inclusive.
int charToAlphabetIndex(char character);

// Function normalises an Index Position value so that it is within the range
// of 0-25 inclusive.
// If value > 25, then 26 is subtracted until desired property is derived.
// If value < 0, then 26 is subtracted until desired property is derived.
void normaliseIndexPosition(int &indexPosition);
