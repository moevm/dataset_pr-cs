#include "sort_latin.h"

size_t check_latin(const Sentence *sentence){
    const wchar_t alphabet[] = LATIN_CHARS;
    size_t count = 0;
    for (size_t i=0;i<sentence->len;i++){
        if (wcschr(alphabet, sentence->data[i])){
        count++;
        }
    }
    return count;
}


int compare_latin(const void *a, const void  *b){
    const Sentence *first = *(const Sentence**)a;
    const Sentence *second = *(const Sentence**)b;
    size_t first_latin = check_latin(first);
    size_t second_latin = check_latin(second);
    return second_latin - first_latin;
}

void sort_latin(Text *text){
    qsort(text->data, text->len, sizeof(Sentence*), compare_latin);
}