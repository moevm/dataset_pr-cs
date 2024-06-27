#pragma once

#include "console.h"
#include "sentence.h"
#include "stringswork.h"
#include <stdbool.h>


typedef struct Text {
    size_t size;
    size_t capacity;
    Sentence** data;
} Text;


#define ALLOC_TEXT 5
Text* realloc_text(Text* text);

Text* text_initialization();

Text* text_free(Text* text);

Text* add_sentence(Text* text, Sentence* sent);

Text* read_text();

Text* restruct(Text* text);

Text* unique(Text* text);

Text* apply_fix_endings(Text* text);

int sentence_compare_words_count(const void* left, const void* right);

Text* sort_by_words_count(Text* text);

Text* filter_longer_than_ten(Text* text);

Text* double_word_in_every_sentence(Text* text);
