#include "braille.h"

int encode_character(const char ch, char braille[20]) {

    int encode_size = 0;

    strcpy(braille, "");

    if (isdigit(ch) != 0) {

        strcat(braille, "..0000");
        encode_size += 6;
    }

    if ((toupper(ch) == ch) && (isalpha(ch) != 0)) {
        strcat(braille, ".....0");
        encode_size += 6;
    }

    encode_size += 6;
    switch(tolower(ch)) {
    case 'a':
    case '1':
        strcat(braille, "0.....");
        break;
    case 'b':
    case '2':
        strcat(braille, "00....");
        break;
    case 'c':
    case '3':
        strcat(braille, "0..0..");
        break;
    case 'd':
    case '4':
        strcat(braille, "0..00.");
        break;
    case 'e':
    case '5':
        strcat(braille, "0...0.");
        break;
    case 'f':
    case '6':
        strcat(braille, "00.0..");
        break;
    case 'g':
    case '7':
        strcat(braille, "00.00.");
        break;
    case 'h':
    case '8':
        strcat(braille, "00..0.");
        break;
    case 'i':
    case '9':
        strcat(braille, ".0.0..");
        break;
    case 'j':
    case '0':
        strcat(braille, ".0.00.");
        break;
    case 'k':
        strcat(braille, "0.0...");
        break;
    case 'l':
        strcat(braille, "000...");
        break;
    case 'm':
        strcat(braille, "0.00..");
        break;
    case 'n':
        strcat(braille, "0.000.");
        break;
    case 'o':
        strcat(braille, "0.0.0.");
        break;
    case 'p':
        strcat(braille, "0000..");
        break;
    case 'q':
        strcat(braille, "00000.");
        break;
    case 'r':
        strcat(braille, "000.0.");
        break;
    case 's':
        strcat(braille, ".000..");
        break;
    case 't':
        strcat(braille, ".0000.");
        break;
    case 'u':
        strcat(braille, "0.0..0");
        break;
    case 'v':
        strcat(braille, "000..0");
        break;
    case 'w':
        strcat(braille, ".0.000");
        break;
    case 'x':
        strcat(braille, "0.00.0");
        break;
    case 'y':
        strcat(braille, "0.0000");
        break;
    case 'z':
        strcat(braille, "0.0.00");
        break;
    case '.':
        strcat(braille, ".0..00");
        break;
    case ',':
        strcat(braille, ".0....");
        break;
    case ';':
        strcat(braille, ".00...");
        break;
    case '-':
        strcat(braille, "..0..0");
        break;
    case '!':
        strcat(braille, ".00.0.");
        break;
    case '?':
        strcat(braille, ".00..0");
        break;
    case '(':
    case ')':
        strcat(braille, ".00.00");
        break;
    default:
        encode_size -= 6;
        return -1;
        break;
    }

    braille[encode_size] = '\0';
    return strlen(braille);
}

void encode(const char* plaintext, char braille[512]) {

    if (plaintext[0] == '\0') {
        braille[0] = '\0';
        return;
    }

    int length = encode_character(plaintext[0], braille);

    return encode(plaintext + 1, braille + length);

}

void print_braille(const char *plaintext, ostream& output) {

    char braille[512];
    

    encode(plaintext, braille);

    for (int i = 0; i < 3; i++) {
        for (int j = 0; braille[j] != '\0'; j += 6){

            output << braille[j + i] << braille[j + i + 3] << "  ";
        }

        output << "\n";
    }

    for (int j = 0; plaintext[j] != '\0'; j++) {

        if (((isdigit(plaintext[j]) != 0) || (toupper(plaintext[j]) == plaintext[j])) && (ispunct(plaintext[j]) == 0)) {
            output << "    " << plaintext[j] << "   ";
        } else {
            output << plaintext[j] << "   ";
        }
    }
}