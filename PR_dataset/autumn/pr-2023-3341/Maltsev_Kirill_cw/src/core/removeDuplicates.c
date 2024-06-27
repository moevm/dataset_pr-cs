#include <stdlib.h>
#include <wchar.h>
#include <wctype.h>

#include "structures.h"
#include "bst.h"

wchar_t* sentenceToUpper(Sentence* sentence) {
    wchar_t* cpy = (wchar_t*) calloc( wcslen(sentence->line)+1, sizeof(wchar_t) );
    wcpcpy(cpy, sentence->line);
    for (int j=0; j<wcslen(cpy); j++) {
        cpy[j] = towupper(cpy[j]);
    }
    return cpy;
}

void fillBstBySentences(Bst* bst, Text* text) {
    for (int i=0; i<text->sentencesNumber; i++) {
        wchar_t* cpy = sentenceToUpper(&text->sentences[i]);
        insert(bst, cpy);
    }
}

void removeDuplicates(Text* text) {
    Bst* bst = createBst();
    fillBstBySentences(bst, text);
    
    int j = 0;
    for (int i=0; i<text->sentencesNumber; i++) {
        
        wchar_t* cpy = sentenceToUpper(&text->sentences[i]);

        if (find(bst, cpy) == 1) {
            text->sentences[j] = text->sentences[i];
            j++;
        }
    }
    text->sentencesNumber = j;
    free(bst);
}