// Author: Louis Heery (lah119)
// Last Updated:

#include <string>
#include <functional>
#include <iostream>

class Reflector  {

private:


public:

  Reflector(char* reflectorFile);

  int reflectorConnections[26];

  int forward(int characterIndex);

  int setupReflector(char* reflectorFile);
};
