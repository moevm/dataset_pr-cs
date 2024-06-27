#include "free_space.h"

void free_space(struct Text text) {
    for (size_t i = 0; i < text.number_of_sentences; i++)
    {
        free(text.text[i]->sentence);
        free(text.text[i]);
    }
    free(text.text);
}