#include <ctype.h>
#include <stdlib.h>
#include <wchar.h>
#include <wctype.h>
#include <locale.h>
#include <ctype.h>

#include "structures.h"

void delete(struct Text* text) {
    for (int i = 0; i < text->len; ++i) {
        wchar_t* pred = (wchar_t*)malloc(sizeof(wchar_t) * (1 + text->sentences[i]->len));
        if (pred == NULL) {
            wprintf(L"Error: Unable to allocate memory for the pred [fn: delete]");
            return;
        }
        wcsncpy(pred, text->sentences[i]->sentence, 1 + text->sentences[i]->len);

        wchar_t* pt;
        wchar_t* pwc = wcstok(pred, L" ,.-:;", &pt);
        int wordsCount = 0;
        int shortWordsCount = 0;
        while (pwc != NULL) {
            int length = wcslen(pwc);
            wordsCount++;
            if (length <= 3) {
                shortWordsCount++;
            }
            pwc = wcstok(NULL, L" ,.-:;", &pt);
        }
        if (wordsCount == shortWordsCount) {
            free(text->sentences[i]->sentence);
            free(text->sentences[i]);
            text->len--;
            for (size_t j = i; j < text->len; ++j) {
                text->sentences[j] = text->sentences[j + 1];
            }
            i--;
        }
        free(pred);
    }
}