#include <wchar.h>
#include <wctype.h>
#include "structures.h"

void new_func(struct Text * textStructured, int size) {

    wchar_t *token;
    wchar_t *buff;

    for (int i = 0; i < textStructured->len; i++) {
        token = wcstok(textStructured->sentences[i]->sentence, L" ", &textStructured->sentences[i]->sentence);
        while (token != NULL) {
            if (wcslen(token) > size) {
                wprintf(L"(большое слово) ");
            } else {
                wprintf(L"%ls ", token);
            }
            if (token[wcslen(token) - 1] == ',') {
                wprintf(L"\b,");
            } 
            token = wcstok(NULL, L" ", &textStructured->sentences[i]->sentence);
        }
    }
    wprintf(L"\b.\n");
}   