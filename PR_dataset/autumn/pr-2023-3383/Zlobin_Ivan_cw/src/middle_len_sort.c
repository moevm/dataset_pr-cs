#include "middle_len_sort.h"

int cmp(const void *key, const void *base){
    float e=0.00001;
    struct Sentence *a=*(struct Sentence**)key;
    struct Sentence *b=*(struct Sentence**)base;
    
    if(a->midlen-b->midlen<e && a->midlen-b->midlen>0) return 0;
    else {
        if(a->midlen-b->midlen>e) return 1;
        else return -1;
    }
}

void middle_len_sort(struct Text *text){
    len_count(text);
    qsort(text->sentences, text->num_of_sent, sizeof(struct Sentence*), cmp);
}
