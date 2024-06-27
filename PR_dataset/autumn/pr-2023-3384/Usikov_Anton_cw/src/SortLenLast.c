#include "SortLenLast.h"

int compare_sentences(const void* a, const void* b) {
    const struct Sentence* sentence_a = *(const struct Sentence**)a;
    const struct Sentence* sentence_b = *(const struct Sentence**)b;
    
    int length_a = sentence_a->l;
    int length_b = sentence_b->l;
    
    wchar_t* last_word_a = sentence_a->str + length_a - 1;
    while (last_word_a > sentence_a->str && !iswalpha(*last_word_a)) {
        last_word_a--;
    }
    
    wchar_t* last_word_b = sentence_b->str + length_b - 1;
    while (last_word_b > sentence_b->str && !iswalpha(*last_word_b)) {
        last_word_b--;
    }
    
    int last_word_length_a = 0;
    while (last_word_a > sentence_a->str && iswalpha(*last_word_a)) {
        last_word_a--;
        last_word_length_a++;
    }
    
    int last_word_length_b = 0;
    while (last_word_b > sentence_b->str && iswalpha(*last_word_b)) {
        last_word_b--;
        last_word_length_b++;
    }
    
    return last_word_length_a - last_word_length_b;
}

void SortLenLast(struct Text* T) {
    qsort(T->txt, T->l, sizeof(struct Sentence*), compare_sentences);
}
