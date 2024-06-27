#include <stdlib.h>
#include <ctype.h>
#include "../header/sort_strings_by_uppercase_count.h"

int countUpperCaseLetters(const char* str) {
    int count = 0;
    while (*str != '\0') {

        if (isupper(*str)) {
            count++;
        }
        str++;
    }
    return count;
}


int compareUpperCaseCount(const void* a, const void* b) {
    const char* strA = *(const char**)a;
    const char* strB = *(const char**)b;

    if (strA == NULL && strB == NULL) {
        return 0;
    }
    if (strA == NULL) {
        return 1;
    }
    if (strB == NULL) {
        return -1;
    }

    int upperCountA = countUpperCaseLetters(strA);
    int upperCountB = countUpperCaseLetters(strB);

    return upperCountB - upperCountA;
}


void sortStringsByUppercaseCount(char** strings, int* numStrings) {
    qsort(strings, *numStrings, sizeof(char*), compareUpperCaseCount);
}
