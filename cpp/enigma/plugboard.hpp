// Author: Louis Heery (lah119)
// Last Updated: 9th November 2019

#include <string>
#include <functional>
#include <iostream>


// Plugboard Class is the Parent Class to the various components of the Enigma Machine
class Plugboard {

private:

  int numberOfConnectionedLetters; // Number of Letters connect to another letter.

public:

  // Plugboard Class is the Child Class to the Enigma Machine
  Plugboard(char* plugboardFile);

  // Defines the letter which each letter is connected to in Plugboard
  int plugboardConnections[26];

  // Function setups any optional Connections between pairs of letters in the
  // Plugboard.
  // INPUT: Char Array containing File address of file specifying the letter
  //         connections of the Plugboard.
  // OUTPUT: Returns 0 if correctly setup.
  int setupPlugboard(char* plugboardFile);

  // Function passes a single character through the Plugboard component of the
  // Enigma machine.
  // INPUT: Character to be passed through Plugboard.
  // OUTPUT: Resulting Character outputted by Plugboard.
  int forward(int characterIndex);

};
