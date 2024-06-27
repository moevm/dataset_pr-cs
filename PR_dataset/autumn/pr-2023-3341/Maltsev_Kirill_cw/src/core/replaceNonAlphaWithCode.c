#include <stdlib.h>
#include <wchar.h>
#include <wctype.h>

#include "structures.h"

void getNewLength(Sentence* sentence, int* newLength) {
    for (int j=0; j<sentence->sentenceSize; j++) {
        if (!iswalpha(sentence->line[j])) {
            wchar_t* code = (wchar_t*) calloc(100, sizeof(wchar_t));
            swprintf(code, 10, L"%d", (int) sentence->line[j]); 
            (*newLength) += wcslen(code);
        }
    }
}

void rewriteSentence(Sentence* sentence, int newLength) {
    wchar_t* temp = (wchar_t*) calloc(newLength+1, sizeof(wchar_t));
    int q = 0;
    for (int j=0; j<sentence->sentenceSize; j++) {
        if (!iswalpha(sentence->line[j])) {
            wchar_t* code = (wchar_t*) calloc(100, sizeof(wchar_t));
            swprintf(code, 10, L"%d", (int) sentence->line[j]);
            for (int k=0; k<wcslen(code); k++) {
                temp[q] = code[k];
                q++;
            }
        } else {
            temp[q] = sentence->line[j];
            q++;
        }
    }
    sentence->line = (wchar_t*) calloc(newLength+1, sizeof(wchar_t));
    sentence->sentenceSize = newLength;
    wcscpy(sentence->line, temp);
}

void replaceNonAlphaWithCode(Text* text) {
    for (int i=0; i<text->sentencesNumber; i++) {
        int newLength = text->sentences[i].sentenceSize;
        getNewLength(&text->sentences[i], &newLength);
        rewriteSentence(&text->sentences[i], newLength);
    }
}