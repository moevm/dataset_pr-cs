#include <wchar.h>

#define SEP L" ,.\n\t"

int len_third(wchar_t* sentence) {
    wchar_t new_sentence[wcslen(sentence)+1];
    wcscpy(new_sentence, sentence);
    wchar_t *word;
    wchar_t *ptr;
    int len = 0;
    word = wcstok(new_sentence, SEP, &ptr);
    word = wcstok(NULL, SEP, &ptr);
    word = wcstok(NULL, SEP, &ptr);
    if (word != NULL) len = wcslen(word);
    return len;
}