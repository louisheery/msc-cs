#include "words.h"
#include <iostream>
#include <cctype>
using namespace std;

void reverse(const char str1[], char str2[]) {

    int str1len = strlen(str1);

    for (int i = str1len; i > 0; i--)
    {
        str2[str1len - i] = str1[i - 1];
    }

    str2[str1len] = '\0';
}

int compare(const char str1[], const char str2[]) {

    while(!isalpha(str1[0]) && str1[0] != '\0') {
        str1++;
    }

    while (!isalpha(str2[0]) && str2[0] != '\0')
    {
        str2++;
    }

    if (toupper(str1[0]) != toupper(str2[0])) {
        return 0;
    }

    if (str1[0] == '\0' && str2[0] == '\0') {
        return 1;
    }

    return compare(str1 + 1, str2 + 1);
}

int palindrome(const char sentence[]) {

    int length = strlen(sentence);
    char sentenceReverse[length];
    reverse(sentence, sentenceReverse);
    return compare(sentence, sentenceReverse);

}

int anagram(const char str1[], const char str2[]) {

    char* str1sorted = sorted_array(str1);
    char* str2sorted = sorted_array(str2);

    int comp = compare(str1sorted, str2sorted);

    return comp;
}

char* sorted_array(const char str[]) {

    int length = strlen(str);
    char* strCopy = new char[length + 1];
    strncpy(strCopy, str, length);

    for (int i = 0; i < length; i++) {

        for (int j = 0; j < length - i - 1; j++) {

            if (toupper(strCopy[j]) > toupper(strCopy[j + 1]))
            {
                char temp = strCopy[j + 1];
                strCopy[j + 1] = strCopy[j];
                strCopy[j] = temp;
            }
        }
    }

    return strCopy;

}