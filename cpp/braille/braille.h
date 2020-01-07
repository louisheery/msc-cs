#include <string.h>
#include <cctype>
#include <iostream>
using namespace std;

int encode_character(const char ch, char braille[20]);

void encode(const char* plaintext, char braille[512]);

void print_braille(const char* plaintext, ostream& output);