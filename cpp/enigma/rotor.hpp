// Author: Louis Heery (lah119)
// Last Updated:

#include <string>
#include <functional>
#include <iostream>

class Rotor {

private:

  int currentPositionOfRotor;

public:

  Rotor(char* rotorFile, int rotorNumberInput);

  int setupRotor(char* rotorFile, int rotorNumberInput);

  int rotorConnections[26];

  int rotorNotches[26];

  int numberOfNotches;

  bool rotorSetupToMove; // Linked List of the number of rotors in the enigma.

  int rotorNumber;

  int forward(int characterIndex);

  int backward(int characterIndex);

  int findCurrentPositionOfRotor();

  void setCurrentPositionOfRotor(int position);

  void checkRotorIsAtNotchPosition();

};
