#pragma once
#include "struct.h"
int not_unique_sentence(sentence* sen1, sentence* sen2);

void free_sentence(sentence* sent);

void free_text(text text_exp);

int compare(const void* sent1, const void* sent2);

size_t count_words(sentence* sent);
