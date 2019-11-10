// Author: Louis Heery (lah119)
// Last Updated: 9th November 2019

#include <string>
#include <functional>
#include <iostream>


// Reflector Class is the Parent Class to the various components of the Enigma Machine
class Reflector  {

public:

  // Reflector Class is the Child Class to the Enigma Machine
  Reflector(char* reflectorFile);

  // Defines the letter which each letter is connected to in Reflector
  int reflectorConnections[26];

  // Function setups up the Connections which connect each of the letters in
  // the Reflector to 1 other letter.
  // INPUT: Char Array containing File address of file specifying the letter
  //         connections of the Reflector.
  // OUTPUT: Returns 0 if correctly setup.
  int setupReflector(char* reflectorFile);

  // Function passes a single character through the Reflector component of the
  // Enigma machine.
  // INPUT: Character to be passed through Reflector.
  // OUTPUT: Resulting Character outputted by Reflector.
  int forward(int characterIndex);
};
