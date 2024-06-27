#include "latin_letter_processing.h"

// Function 3
void sort_by_latin_letters(int *err)
{
    if (*err) return;
    Text *text = Text_read(err);
    if (*err) return;
    text = basic_processing(text, err);
    if (*err) return;
    qsort(text->sentences, text->size, sizeof(Sentence *), cmp_latin);
    Text_print(text);
    Text_delete(&text);
}

int count_latin_letters(Sentence *sentence)
{
    size_t latin_letter_count = 0;
    for (size_t i = 0; i < sentence->size; ++i)
        if (iswalpha(sentence->sentence[i]) && (int)sentence->sentence[i] < 128)
            latin_letter_count++;
    return latin_letter_count;
}

int cmp_latin(const void *sentence1, const void *sentence2)
{
    Sentence *first = *(Sentence **)sentence1;
    Sentence *second = *(Sentence **)sentence2;
    return count_latin_letters(second) - count_latin_letters(first);
}