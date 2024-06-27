#pragma once

#include "structs_libraries.h"
#include "supporting_functions.h"


int read_number();
void read_text(struct Text *text);
void read_sentences(struct Sentence **sentences_array, struct Text *text);
void fill_the_structure(struct Sentence *sentences_array, size_t sentences_count);
void clean_memory(struct Sentence *sentences_array, struct Text *text);
