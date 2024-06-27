#include <wchar.h>
#include "../include/struct.h"

int countMinutes(Sentence* sentence) {
    int seconds = 0;

    wchar_t* words[sentence->size];
    int size = 0;

    wchar_t* state;
    wchar_t* token = wcstok(wcsdup(sentence->sentence), L" ,", &state);

    while (token != NULL) {
        words[size++] = token;
        token = wcstok(NULL, L" ,", &state);
    }

    wchar_t* end;
    for(int j=0; j<size; j++) {
        if (wcscmp(words[j], L"sec") == 0)
            seconds += wcstol(words[j-1], &end, 10);
    }

    return seconds;
}