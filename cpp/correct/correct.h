#ifndef CORRECT_H
#define CORRECT_H

void ascii_to_binary(char letter, char *output);
char binary_to_ascii(char *binary);
void text_to_binary(const char *str, char binary[512]);
void binary_to_text(const char *str, char text[32]);

char parity(const char a, const char b, const char c);
char parity(const char a, const char b, const char c, const char d);
int binary_to_decimal(char binary[4]);
bool all_zero(const char a, const char b, const char c);
char flip_bit(const char a);
void add_error_correction(const char *data, char corrected[512]);
int decode(const char *received, char decoded[512]);

#endif