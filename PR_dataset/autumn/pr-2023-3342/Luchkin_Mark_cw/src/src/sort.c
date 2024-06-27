#include "sort.h"

int compareSentences(const void *a, const void *b){
    const Sentence *sentenceA = (const Sentence *)a;
    const Sentence *sentenceB = (const Sentence *)b;

    if (sentenceA->averageWordsLength < sentenceB->averageWordsLength) {
        return -1;
    } else if (sentenceA->averageWordsLength > sentenceB->averageWordsLength) {
        return 1;
    } else {
        return 0;
    }
}

void sortSentences(Text *text){
    qsort(text->sentences, text->size, sizeof(Sentence), compareSentences);
}