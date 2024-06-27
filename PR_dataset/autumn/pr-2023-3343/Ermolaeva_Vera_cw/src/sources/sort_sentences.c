#include <wchar.h>
#include <stdlib.h>
#include "../include/struct.h"

int getCode(wchar_t* sentence) {
    int code = 0;
    
    wchar_t* state;
    wchar_t* first_word = wcstok(wcsdup(sentence), L" ,", &state);

    for(int i=0; i<wcslen(first_word); i++)
        code += first_word[i];

    return code;
}

int cmp(const void* a, const void* b) {
    return getCode(*(wchar_t**)a) - getCode(*(wchar_t**)b);
}

void sortBySum(Text* text) {
    qsort(text->sentences, text->real_size, sizeof(Sentence), cmp);
}