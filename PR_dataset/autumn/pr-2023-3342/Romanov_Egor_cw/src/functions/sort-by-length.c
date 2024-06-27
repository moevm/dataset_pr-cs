#include "../headers/sort-by-length.h"

int cmp(const void *a, const void *b){


    struct Sentence *first_sent = (struct Sentence*)a;
    struct Sentence *second_sent = (struct Sentence*)b;

    double len_of_first_sentence = 1.0;
    double len_of_second_sentence = 1.0;
    for (size_t i=0;i<first_sent->quantity_of_words;i++){
        len_of_first_sentence *= (double)wcslen(first_sent->words[i].word);
    }
    for (size_t i=0;i<second_sent->quantity_of_words;i++){
        len_of_second_sentence *= wcslen(second_sent->words[i].word); 
    }

    if (len_of_first_sentence > len_of_second_sentence){
        return 1;
    }
    if (len_of_first_sentence < len_of_second_sentence){
        return -1;
    }
    return 0;
}

void sort_by_length(struct Text text){
    text = return_reworked_text(text);
    split_sentences_on_words(text);
    qsort(text.sentences, text.quantity_of_sentences, sizeof(struct Sentence), cmp);
    output(text);
    free_text(text);
}