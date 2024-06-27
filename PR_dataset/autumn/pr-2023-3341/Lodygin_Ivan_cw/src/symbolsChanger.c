#include <wchar.h>
#include <stdlib.h>
#include "structures.h"
#include "wordSymbolChanger.h"
#include "getSeparators.h"
#include "wordSymbolChanger.h"

#define SEP L" ,.\n\t"

void symbolsChanger(struct Text text) {
    wchar_t *sentence = calloc(1, sizeof(wchar_t));
    wchar_t *word;
    wchar_t *ptr;
    wchar_t **separators;
    int k;
    for(int i = 0; i<text.n; i++){
        sentence = realloc(sentence, sizeof(wchar_t)*(wcslen(text.sents[i]->str)+1));
        wcscpy(sentence, text.sents[i]->str);
        separators = getSeparators(sentence);
        wcscpy(sentence, text.sents[i]->str);
        word = wcstok(sentence, SEP, &ptr);
        if(word != NULL) {
            wcscpy(word, wordSymbolChanger(word));
            wprintf(L"%ls", word);
            wprintf(L"%ls", separators[0]);
        }
        k=1;
        while(1) {
            word = wcstok(NULL, SEP, &ptr);
            if(word == NULL) break;
            wcscpy(word, wordSymbolChanger(word));
            wprintf(L"%ls", word);
            wprintf(L"%ls", separators[k]);
            k++;
        }
        wprintf(L"%c%c", L'.', L'\n');
    }
}