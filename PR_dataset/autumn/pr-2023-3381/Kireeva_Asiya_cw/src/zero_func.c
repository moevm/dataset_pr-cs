#include "zero_func.h"

void zero_func() {
    struct Text text = get_text();
    for (int i = 0; i < text.number_of_sentences; i++) {
        wprintf(L"%ls\n", text.text[i]->sentence);
    }
    free_space(text);
}