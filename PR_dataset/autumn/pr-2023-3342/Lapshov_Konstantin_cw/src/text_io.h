#pragma once
#include "structures.h"

int check_similar_sen(struct Text text, struct Sentence sen);

void input_text(struct Text* text);
void add_symbol(struct Word *word, wchar_t symbol);
void free_sentence(struct Sentence sentence);

size_t check_for_end_of_word(struct Word word, wchar_t symbol, wchar_t last_symbol);

void output_text(struct Text text);
void free_text(struct Text* text);

void print_reference();