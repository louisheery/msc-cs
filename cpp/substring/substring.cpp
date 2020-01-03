#include "substring.h"

bool is_prefix(const char *first, const char *second) {

    if (*(first) == '\0') {
        return true;
    }

    if (*(first) == *(second)) {
        return is_prefix(first + 1, second + 1);
    }

    return false;

}

int substring_position(const char *first, const char *second) {

    if ((*first == '\0') && (*second == '\0')) {
        return 0;
    }

    if (*first == '\0') {
        return 0;
    }

    for (int i = 0; second[i] != '\0'; i++) {
        if (is_prefix(first, second + i)) {
            return i;
        }
    }

    return -1;

/*
    static int count = 0;

    if ((*first == '\0') && (*second == '\0')) {
        //cout << "&&" << endl;
        return count;
    }

    if (*first == '\0') {
        return 0;
    }

    if (*second == '\0') {
        return -1;
    }

    if (is_prefix(first, second)) {
        return count;
    }

    count++;

    return substring_position(first, second + 1);
    */
}