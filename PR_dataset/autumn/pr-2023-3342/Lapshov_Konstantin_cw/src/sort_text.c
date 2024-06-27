#include "sort_text.h"

void sort_text(struct Text *text){
    for (int i = 0; i < text->quantity_of_sentences; ++i) {
        struct Sentence *curr_sen = &text->sentences[i];

        if(quantity_of_latin(*curr_sen)){
            qsort(curr_sen->words, curr_sen->quantity_of_words, sizeof(struct Word), compare_for_latin);
        }
    }
}
int compare_for_latin(const void *a, const void *b){
    const struct Word *word_one = (const struct Word *)a;
    const struct Word *word_two = (const struct Word *)b;

    int latins_in_first_str = 0;
    int latins_in_second_str = 0;

    for (int i = 0; i < word_one->quantity_of_letters; i++) {
        if (towlower(word_one->letters[i]) >= L'a' && towlower(word_one->letters[i]) <= L'z') latins_in_first_str++;
    }

    for (int i = 0; i < word_two->quantity_of_letters; i++) {
        if (towlower(word_two->letters[i]) >= L'a' && towlower(word_two->letters[i]) <= L'z') latins_in_second_str++;
    }

    return latins_in_second_str - latins_in_first_str;
}