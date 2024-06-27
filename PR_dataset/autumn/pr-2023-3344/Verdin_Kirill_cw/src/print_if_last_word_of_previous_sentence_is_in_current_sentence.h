#pragma once
#include "text.h"

int is_last_word_in_sentence(Word *word, Sentence *str2);
void print_sentences_if_last_word_of_previous_sentence_is_in_current_sentence(Text *txt);