#include <wchar.h>
#include <wctype.h>
#include <stdlib.h>
#include <locale.h>

#include "structs.h"
#include "input.h"
#include "output.h"
#include "free_memory.h"
#include "checking_symbol.h"

int cmp(const void* a, const void* b) {
    if (((Sentence*)a)->count_latin > ((Sentence*)b)->count_latin)
        return -1;
    if (((Sentence*)a)->count_latin < ((Sentence*)b)->count_latin)
        return 1;
    return 0;
}

void sort_latin() {
    Text* text = (Text*)malloc(sizeof(Text));
    text->sentences = (Sentence*)malloc(sizeof(Sentence));
    input_text(text);
    for (int i = 0; i < text->size_text; i++) {
        int count_latin = 0;
        for (int j = 0; j < text->sentences[i].size_str; j++) {
            if (is_latin(text->sentences[i].str[j])) {
                count_latin++;
            }
        }
        text->sentences[i].count_latin = count_latin;
    }
    qsort(text->sentences, text->size_text, sizeof(Sentence), cmp);
    output_text(text);
    free_text(text);
}
