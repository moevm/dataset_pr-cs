#include <wchar.h>
#include <stdlib.h>
#include "structures.h"
#include "word_symbol_changer.h"
#include "get_separators.h"
#include "word_symbol_changer.h"

#define SEP L" ,.\n\t"

void symbols_changer(struct Text text) {
    wchar_t *sentence = calloc(1, sizeof(wchar_t));
    wchar_t *word;
    wchar_t *ptr;
    wchar_t **separators;
    int k;
    for(int i = 0; i<text.n; i++){
        sentence = realloc(sentence, sizeof(wchar_t)*(wcslen(text.sents[i]->str)+1));
        wcscpy(sentence, text.sents[i]->str);
        separators = get_separators(sentence);
        wcscpy(sentence, text.sents[i]->str);
        word = wcstok(sentence, SEP, &ptr);
        if(word != NULL) {
            wcscpy(word, word_symbol_changer(word));
            wprintf(L"%ls", word);
            wprintf(L"%ls", separators[0]);
        }
        k=1;
        while(1) {
            word = wcstok(NULL, SEP, &ptr);
            if(word == NULL) break;
            wcscpy(word, word_symbol_changer(word));
            wprintf(L"%ls", word);
            wprintf(L"%ls", separators[k]);
            k++;
        }
        wprintf(L"%c%c", L'.', L'\n');
    }
}