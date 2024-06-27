#ifndef CW_OUTPUT_H
#define CW_OUTPUT_H

#include "text.h"

void print_text(Text *text);

void print_sentence_by_tokens(Sentence *sentence);

void print_help();

void print_err_no_mem();

void print_err_no_option();

void print_err_invalid_option();

void print_err_text_empty();

void print_err_not_enough_words_in_sentence(size_t sentence_index);

#endif //CW_OUTPUT_H
