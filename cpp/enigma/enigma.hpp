// Author: Louis Heery (lah119)
// Last Updated: 9th November 2019

#include <string>
#include <functional>
#include <iostream>
#include "plugboard.hpp"
#include "reflector.hpp"
#include "rotor.hpp"


// Enigma Class is the Parent Class to the various components of the Enigma Machine
class Enigma {

private:
  Plugboard *plugboard;
  Reflector *reflector;

  int numberOfRotors;
  Rotor ** rotors;

public:

  // Constructor: Which initialises Enigma machine with its subclasses
  // of Plugboard, Reflector, Rotors (dependent on number of input arguments).
  // INPUT: Number of Arguments passed into Program, Linked List of Input File names.
  // OUTPUT: Constructed Enigma Class.
  Enigma(int numberOfArgs, char** inputFiles);

  // Function will setup the configuation of Enigma machine's rotor positions
  // by assigning their 'currentPositionOfRotor' attribute
  // INPUT: Char Array containing File address of file specifying the start
  //         position of each rotor.
  // OUTPUT: Rotor Object's 'currentPositionOfRotor' attribute will be initialised.
  int setupRotorPos(char* rotorPosFile);

  // Function will decode a character
  // INPUT: Character to be decoded/encoded by Enigma Machine
  // OUTPUT: Decoded/Encoded Character.
  char decodeCharacter(char inputCharacter);

  // Function will rotate rightmost rotor of Enigma machine, and potentially
  // cause other rotors (if present) to also rotate, if their right-hand rotor's
  // notch causes them to rotate.
  void rotate();

  // Function checks whether any of the rotors are setup to cause the rotor
  // on their left-hand-side to rotate before the enigma machine has been run.
  void initialCheck();

  // Destructor: Deinitialises Enigma Machine Object
  ~Enigma();
};
