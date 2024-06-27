#include <stdio.h>
#include <wchar.h>
#include <stdlib.h>
#include "header_files/structures.h"

int cmp(const void* a, const void* b){
    const Sentence* first = (const Sentence*)a;
    const Sentence* second = (const Sentence*)b;
    return first->words[0].len - second->words[0].len;
}

void sort(Text text){
    qsort(text.sentences, text.countSentences, sizeof(Sentence), cmp);
    for (int i = 0; i < text.countSentences; i++){
        wprintf(L"%ls\n", text.sentences[i].content);
    }
}