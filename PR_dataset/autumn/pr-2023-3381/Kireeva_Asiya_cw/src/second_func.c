#include "second_func.h"

int compare(const void *a, const void *b) {
    const struct Sentence **k = (const struct Sentence **) a;
    const struct Sentence **m = (const struct Sentence **) b;
    if (((*k)->first_word_summ) > ((*m)->first_word_summ)) return 1;
    if (((*k)->first_word_summ) < ((*m)->first_word_summ)) return -1;
    return 0;
}

void second_func() {
    struct Text text = get_text();
    for (int i = 0; i < text.number_of_sentences; i++) {
        for (int j = 0; j < text.text[i]->number_of_letters; j++) {
            if (text.text[i]->sentence[j] == L' ' || text.text[i]->sentence[j] == L',' ||
                text.text[i]->sentence[j] == L'.' || text.text[i]->sentence[j] == L'\n') {
                break;
            }
            text.text[i]->first_word_summ += (int) text.text[i]->sentence[j];
        }
    }
    qsort(text.text, text.number_of_sentences, sizeof(struct Sentence **), compare);
    for (int i = 0; i < text.number_of_sentences; i++) {
        wprintf(L"%ls\n", text.text[i]->sentence);
    }
    free_space(text);
}