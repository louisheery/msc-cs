#include "soundex.h"

char encode_letter(const char surnameLetter)
{

    switch (surnameLetter)
    {

    case 'b':
    case 'f':
    case 'p':
    case 'v':
        return '1';
        break;

    case 'c':
    case 'g':
    case 'j':
    case 'k':
    case 'q':
    case 's':
    case 'x':
    case 'z':
        return '2';
        break;

    case 'd':
    case 't':
        return '3';
        break;

    case 'l':
        return '4';
        break;

    case 'm':
    case 'n':
        return '5';
        break;

    case 'r':
        return '6';
        break;

    default:
        return '0';
        break;
    }
}

void encode(const char surname[], char soundex[5]) {

    soundex[0] = surname[0];

    int i = 1;
    int j = 1;
    int previousCharEncode = 0;
    int currentCharEncode;
    while ((i < 4)) {

        if (surname[j] == '\0') {
            break;
        }

        currentCharEncode = encode_letter(surname[j]);

        if (currentCharEncode == '0') {
            j++;
            continue;
        }

        else if (currentCharEncode != previousCharEncode) {
            soundex[i] = currentCharEncode;
            previousCharEncode = currentCharEncode;
            i++;
        }

        j++;
    }

    while (i < 4)
    {
        soundex[i] = '0';
        i++;
    }

    soundex[i] = '\0';

}

int compare(const char one[], const char two[]) {

    if ((one[0] == '\0') || (two[0] == '\0')) {
        return true;
    }

    if (one[0] == two[0]) {
        return compare(one + 1, two + 1);
    }

    return false;

}

int count(const char surname[], const char sentence[]) {

    int count = 0;
    char soundexA[5];
    char soundexB[5];

    encode(surname, soundexA);

    int wordStart;
    int lengthOfWord;
    
    for (int i = 0; sentence[i] != '\0'; i++) {

        if(!isalpha(sentence[i])) {

            lengthOfWord = i - wordStart;

            if (lengthOfWord > 0) {
                char currentWord[lengthOfWord + 1];
                strncpy(currentWord, sentence + wordStart, lengthOfWord);
                currentWord[lengthOfWord] = '\0';
                encode(currentWord, soundexB);
                if (compare(soundexA, soundexB) == true) {
                    count++;
                }
            }

            wordStart = i + 1;
        }

        
    }

    return count;
}