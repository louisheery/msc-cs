#include <iostream>
#include <openssl/sha.h>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <fstream>
#include <sstream>
#include <string>
#include <streambuf>
#include "stamp.h"

using namespace std;

/* You are pre-supplied with the functions below. Add your own 
   function definitions to the end of this file. */

// helper function for internal use only
// transforms raw binary hash value into human-friendly hexademical form
void convert_hash(const unsigned char *str, char *output, int hash_length) {
  char append[16];
  strcpy (output, "");
  for (int n=0; n<hash_length; n++) {
    sprintf(append,"%02x",str[n]);
    strcat(output, append);
  }
}

// pre-supplied helper function
// generates the SHA1 hash of input string text into output parameter digest
// ********************** IMPORTANT **************************
// ---> remember to include -lcrypto in your linking step <---
// ---> so that the definition of the function SHA1 is    <---
// ---> included in your program                          <---
// ***********************************************************
void text_to_SHA1_digest(const char* text, char* digest) {
  unsigned char hash[SHA_DIGEST_LENGTH];
  SHA1( (const unsigned char *) text, strlen(text), hash);
  convert_hash(hash, digest, SHA_DIGEST_LENGTH);
}

/* add your function definitions here */
int leading_zeros(char* digest) {

  // 1. Check digest = hexa
  for (int i = 0; digest[i] != '\0'; i++) {

    int character = (int) (digest[i]);

    if (!(character > 47 && character < 58) && !(character > 96 && character < 103)) {
      return -1;
    }
  }

  // 2. Count number of zeros
  int numberOfZeros = 0;

  for (int i = 0; digest[i] != '\0'; i++) {

    if (digest[i] != '0') {
      return numberOfZeros;
    } else {
      numberOfZeros++;
    }

  }

  return numberOfZeros;

}

bool file_to_SHA1_digest(const char* filename, char* digest) {

  ifstream infile;

  infile.open(filename);
  if(!infile.is_open()) {
    return false;
  }

  stringstream buffer;

  buffer << infile.rdbuf();

  string bufferString = buffer.str();

  const char *text = bufferString.c_str();

  infile.close();

  text_to_SHA1_digest(text, digest);

  return true;
}

bool make_header(const char* recipient, const char* filename, char header[]) {

  char fileText[41];
  file_to_SHA1_digest(filename, fileText);

  for (int i = 0; i < 10000000; i++) {

    string headerText = string(recipient) + string(":") + string(fileText) + string(":") + to_string(i);

    const char* headerTextChar = headerText.c_str();

    char digest[41];

    text_to_SHA1_digest(headerTextChar, digest);

    if (leading_zeros(digest) > 4) {
      strcpy(header, headerTextChar);
      return true;
    }

  }

  return false;

}

MessageStatus check_header(const char* email, const char* header, const char* filename) {
/*
  INVALID_HEADER = -1,
  WRONG_RECIPIENT = -2,
  INVALID_MESSAGE_DIGEST = -3,
  INVALID_HEADER_DIGEST = -4,
  VALID_EMAIL = 1
*/
  // Check Header is Valid
  int headerLength = strlen(header);
  cout << headerLength;

  // get locations of colons
  int colon1location = -1;
  int colon2location = -1;

  for (int i = 0; i < headerLength; i++) {
    
    if (header[i] == ':') {
      cout << header[i] << ":" << i << endl;
      if (colon1location == -1) {
          colon1location = i;
        } else {
          if (colon2location == -1) {
            colon2location = i;
          } else {
            return INVALID_HEADER;
          }
        }
      }
  }

  if ((colon1location == -1) || (colon2location == -1)) {
    return INVALID_HEADER;
  }

  if ((colon1location == 0) || (colon2location == (headerLength - 1))) {
    return INVALID_HEADER;
  }

  if ((colon2location - colon1location < 2)) {
    return INVALID_HEADER;
  }

  // Check Receipient Email is Valid (i.e. 'email' == email in header)
  char headerEmail[colon1location];
  memcpy(headerEmail, header, colon1location);
  headerEmail[colon1location] = '\0';

  for (int i = 0; i < strlen(email); i++) {

    if (email[i] != headerEmail[i]) {
      return WRONG_RECIPIENT;
    }
  }

  // Check Header Digest = Valid i.e. SHA(message1.txt) == headerDigest
  char headerDigest[colon2location - colon1location];
  memcpy(headerDigest, header + colon1location + 1, colon2location - colon1location - 1);
  headerDigest[colon2location - colon1location-1] = '\0';

  char messageDigest[41];
  file_to_SHA1_digest(filename, messageDigest);
  if (strcmp(headerDigest, messageDigest) != 0) {
    
    return INVALID_HEADER_DIGEST;
  }

  // Check Message Digest i.e. that leading_zeros(SHA1(header)) > 5
  char fullDigest[41];

  text_to_SHA1_digest(header, fullDigest);

  if (leading_zeros(fullDigest) < 5) {
    return INVALID_MESSAGE_DIGEST;
  }


  // Else it is a valid email
  return VALID_EMAIL;

}