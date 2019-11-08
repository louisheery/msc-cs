// Author: Louis Heery (lah119)
// Last Updated:

#include <string>
#include <functional>
#include <iostream>
#include "plugboard.hpp"
#include "reflector.hpp"
#include "rotor.hpp"


class Enigma {

private:
  //int plugboardConnections[13][2];

  Plugboard *plugboard;
  Reflector *reflector;

  int numberOfRotors;
  Rotor ** rotors;

public:
  // Constructor
  //Enigma();

  Enigma(int numberOfArgs, char** inputFiles);

  int setupRotorPos(char* rotorPosFile);
  int setupEnigma(int numberOfArgs, char** inputFiles);
  char decodeCharacter(char inputCharacter);
  void rotate();
};
