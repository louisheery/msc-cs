#include <iostream>
#include <string.h>

using namespace std;

/* You are supplied with two helper functions */

/* converts a character into a binary string representation */
void ascii_to_binary(char ch, char *binary)
{
    for (int n = 128; n; n >>= 1)
        *binary++ = (ch & n) ? '1' : '0';
    *binary = '\0';
}

/* converts a binary string representation into a character */
char binary_to_ascii(char *binary)
{
    int ch = 0;
    for (int n = 0, slide = 128; n < 8; n++, slide >>= 1)
    {
        if (binary[n] == '1')
            ch = ch | slide;
    }
    return ch;
}

/* now add your own functions here */
void text_to_binary(const char* str, char binary[512]) {

    if (str[0] == '\0') {
        return;
    }

    char letter = (int) str[0];
    ascii_to_binary(letter, binary);
    return text_to_binary(str + 1, binary + 8);
}

void binary_to_text(const char* str, char text[32]) {

    if (str[0] == '\0') {
        text[0] = '\0';
        return;
    }

    char binary[9];
    strncpy(binary, str, 8);
    //binary[9] = '\0';

    text[0] = binary_to_ascii(binary);

    return binary_to_text(str + 8, text + 1);

}

char parity(const char a, const char b, const char c) {

    char parity;

    (((a + b + c) % 2) == 0) ? parity = '0' : parity = '1';

    return parity;

}

char parity(const char a, const char b, const char c, const char d) {

    char parity;

    (((a + b + c + d) % 2) == 0) ? parity = '0' : parity = '1';

    return parity;

}

bool all_zero(const char a, const char b, const char c) {

    if ((a == '0') && (b == '0') && (c == '0')) {
        return true;
    }

    return false;
}

void add_error_correction(const char *data, char corrected[512]) {

    if (data[0] == '\0') {
        corrected[0] = '\0';
        return;
    }

    corrected[0] = parity(data[0], data[1], data[3]);
    corrected[1] = parity(data[0], data[2], data[3]);
    corrected[2] = data[0];
    corrected[3] = parity(data[1], data[2], data[3]);
    corrected[4] = data[1];
    corrected[5] = data[2];
    corrected[6] = data[3];

    return add_error_correction(data + 4, corrected + 7);

}

int binary_to_decimal(char binary[4]) {

    string number(binary);
    int decimal = 0;

    int base = 1;

    int length = number.length();
    for (int i = length - 1; i >= 0; i--)
    {
        if (number[i] == '1')
            decimal += base;
        base = base * 2;
    }

    return decimal;
}

char flip_bit(const char a) {

    if (a == '0') {
        return '1';
    } else {
        return '0';
    } 
}

int decode(const char* received, char decoded[512]) {

    static int count = 0;

    if (received[0] == '\0') {
        decoded[0] = '\0';
        return count;
    }

    char parity1 = parity(received[3], received[4], received[5], received[6]);
    char parity2 = parity(received[1], received[2], received[5], received[6]);
    char parity3 = parity(received[0], received[2], received[4], received[6]);

    if (all_zero(parity1, parity2, parity3) == false) {

        count++;

        char allParity[4] = {parity1, parity2, parity3, '\0'};
        
        int decimalNumber = binary_to_decimal(allParity);

        (decimalNumber - 1 == 2) ? decoded[0] = flip_bit(received[2]) : decoded[0] = received[2];
        (decimalNumber - 1 == 4) ? decoded[1] = flip_bit(received[4]) : decoded[1] = received[4];
        (decimalNumber - 1 == 5) ? decoded[2] = flip_bit(received[5]) : decoded[2] = received[5];
        (decimalNumber - 1 == 6) ? decoded[3] = flip_bit(received[6]) : decoded[3] = received[6];

        return decode(received + 7, decoded + 4);

    } else {
        decoded[0] = received[2];
        decoded[1] = received[4];
        decoded[2] = received[5];
        decoded[3] = received[6];

        return decode(received + 7, decoded + 4);
    }

    
}