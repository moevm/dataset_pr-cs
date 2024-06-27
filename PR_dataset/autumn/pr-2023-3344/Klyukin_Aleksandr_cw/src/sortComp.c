#include <stdlib.h>
#include <wchar.h>
#include <wctype.h>

#include "structures.h"

int compare(const void *a, const void *b) {
    struct Sentence *sentenceA = *(struct Sentence **)a;
    struct Sentence *sentenceB = *(struct Sentence **)b;

    struct Sentence *copyA = (struct Sentence*)malloc(sizeof(struct Sentence));
    copyA->sentence = malloc((sentenceA->len + 1) * sizeof(wchar_t));
    wcscpy(copyA->sentence, sentenceA->sentence);

    struct Sentence *copyB = (struct Sentence*)malloc(sizeof(struct Sentence));
    copyB->sentence = malloc((sentenceB->len + 1) * sizeof(wchar_t));
    wcscpy(copyB->sentence, sentenceB->sentence);

    wchar_t *inputA = copyA->sentence;
    wchar_t *wordA = wcstok(inputA, L" ,.\n", &inputA);

    wchar_t *inputB = copyB->sentence;
    wchar_t *wordB = wcstok(inputB, L" ,.\n", &inputB);

    wchar_t *lastWordA = wordA;
    wchar_t *lastWordB = wordB;

    while (wordA != NULL) {
        lastWordA = wordA;
        wordA = wcstok(NULL, L" ,.\n", &inputA);
    }
    while (wordB != NULL) {
        lastWordB = wordB;
        wordB = wcstok(NULL, L" ,.\n", &inputB);
    }
    free(copyA->sentence);
    free(copyA);
    free(copyB->sentence);
    free(copyB);
    if(wcslen(lastWordA) > wcslen(lastWordB)){
        return 1;
    }
    else if(wcslen(lastWordA) < wcslen(lastWordB)){
        return -1;
    }
    else if(wcslen(lastWordA) == wcslen(lastWordB)){
        return 0;
    }
}
