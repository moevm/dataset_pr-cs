#pragma once

#include "structs_libraries.h"


void return_error(wchar_t *message);
int compare(const void *first_element, const void *second_element);
int check_sentence_in_array(struct Sentence *sentences_array, size_t sentences_count, wchar_t *sentence);
