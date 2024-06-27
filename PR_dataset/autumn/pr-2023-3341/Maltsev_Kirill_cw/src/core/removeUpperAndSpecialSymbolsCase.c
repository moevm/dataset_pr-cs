#include <wchar.h>
#include <wctype.h>

#include "structures.h"

int checkCase(Sentence* sentence) {
    int flag = 0;
    for (int i=0; i<sentence->sentenceSize; i++) {
        if (sentence->line[i] == L'#' || sentence->line[i] == L'$' || sentence->line[i] == L'^' || sentence->line[i] == L'%' || sentence->line[i] == L'@') flag = 1;
        if (iswupper(sentence->line[i])) return 0;
    }
    return flag;
}

void removeUpperAndSpecialSymbolsCase(Text* text) {
    int j = 0;
    for (int i=0; i<text->sentencesNumber; i++) {
        if (!checkCase(&text->sentences[i])) {
            text->sentences[j] = text->sentences[i];
            j++;
        }
    }
    text->sentencesNumber = j;
}