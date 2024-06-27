#include "sort.h"

int cmp(const void* a, const void*b){
    struct Sentence* sent1 = (struct Sentence*)a;
    struct Sentence* sent2 = (struct Sentence*)b;
    int result1 = 1;
    int result2 = 1;
    for(int i = 0; i < sent1->num_of_words; i++){
        result1 *= wcslen(sent1->words[i]);
    }
    for(int i = 0; i < sent2->num_of_words; i++){
        result2 *= wcslen(sent2->words[i]);
    }
    return result2 <= result1;
}

void sort(struct Text* text){
    qsort(text->text, text->size, sizeof(struct Sentence), cmp);
}