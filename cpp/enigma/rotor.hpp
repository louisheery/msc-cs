// Author: Louis Heery (lah119)


#include <string>
#include <functional>
#include <iostream>


// Rotor Class is the Parent Class to the various components of the Enigma Machine
class Rotor {

private:

  int currentPositionOfRotor; // Current Position of Rotor in Enigma machine

public:

  int rotorConnections[26]; // Defines letter mapping of Rotor
  int rotorNotches[26]; // Location of Rotor Notches on the Rotor Object
  int numberOfNotches; // Number of Notches on the Rotor Object
  bool rotorSetupToMove; // Linked List of the number of rotors in the enigma.
  int rotorNumber; // Unique Number of Rotor in the Enigma Machine

  // Rotor Class is the Child Class to the Enigma Machine
  Rotor(char* rotorFile, int rotorNumberInput);

  // Function setups up the Connections which connect each of the letters in
  // the Reflector to 1 other letter.
  // INPUT: Char Array containing File address of file specifying the letter
  //         connections of the Reflector.
  // OUTPUT: Returns 0 if correctly setup.
  int setupRotor(char* rotorFile, int rotorNumberInput);

  // Function passes a single character through the Rotor component of the
  // Enigma machine in Forward Direction (from Right to Left).
  // INPUT: Character to be passed through Rotor.
  // OUTPUT: Resulting Character outputted by Rotor.
  int forward(int characterIndex);

  // Function passes a single character through the Rotor component of the
  // Enigma machine in Backward Direction (from Left to Right).
  // INPUT: Character to be passed through Rotor.
  // OUTPUT: Resulting Character outputted by Rotor.
  int backward(int characterIndex);

  // Function returns the currentPositionOfRotor attribute.
  int findCurrentPositionOfRotor();

  // Function sets the currentPositionOfRotor attribute to 'position' input value.
  void setCurrentPositionOfRotor(int position);

  // Function checks whether the Rotor's current position is such that
  // a notch is about to rotate the adjacent rotor on the next rotation of rotor.
  void checkRotorIsAtNotchPosition();

};
