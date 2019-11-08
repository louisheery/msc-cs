// Author: Louis Heery (lah119)
// Last Updated:

#include <string>
#include <functional>
#include <iostream>

class Plugboard {

private:

  int numberOfConnectionedLetters;

public:
  Plugboard(char* plugboardFile);

  int plugboardConnections[26];

  int setupPlugboard(char* plugboardFile);

  int forward(int characterIndex);

  int backward(int characterIndex);

};
