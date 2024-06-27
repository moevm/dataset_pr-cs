#pragma once

#include "structs_libraries.h"
#include "supporting_functions.h"


void do_basic_processing(struct Sentence *sentences_array, size_t sentences_count);
void convert_to_date(struct Sentence *sentences_array, size_t sentences_count);
void reverse_sentence(struct Sentence *sentences_array,size_t sentences_count);
void sort_by_first_word(struct Sentence *sentences_array,size_t sentences_count);
void delete_short_words(struct Sentence *sentences_array,size_t sentences_count);
void replace(struct Sentence *sentences_array,size_t sentences_count);
