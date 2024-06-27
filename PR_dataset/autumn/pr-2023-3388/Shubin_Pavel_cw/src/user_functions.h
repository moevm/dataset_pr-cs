#pragma once

#include "structs_libraries.h"
#include "support_functions.h"

int cnt_num_of_secs (struct Text text);
void sort_by_codes_of_first_words (struct Text *text);
void replace_option_chars (struct Text *text);
void delete_sentences_with_three_consonants_in_last_word (struct Text *text);
void palindrome_sentence_func(struct Text *text);
