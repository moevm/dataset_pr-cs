#pragma once
#include "word.h"

typedef struct Sentence
{
    Word **array_of_words;
    int count_words;
    int capacity_words;
    Word **array_of_sep;
    int count_sep;
    int capacity_sep;
} Sentence;

void initial_sentence(Sentence *str);
Sentence *make_sentence();
void expand_array_words(Sentence *str);
void expand_array_sep(Sentence *str);
int sentence_comparison(const Sentence *sent1, const Sentence *sent2);
int sentence_is_in_text(Sentence **array_of_sentences, Sentence *sent, int countsents);
void free_sentence(Sentence *sent);
