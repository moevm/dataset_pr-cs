#pragma once
#include "structures.h" 

void print_sent(struct Text *text, int i);
void print_text(struct Text *text);
int compare_sents(wchar_t *sent1, wchar_t *sent2);
int sent_in_sentences(wchar_t** sentences, wchar_t* sent, int sent_counter);
void search_seps(wchar_t *sentence, struct Text *text);
void read_text(struct Text *text);
void find_palindroms(struct Text *text);
void replace_spec_symbols(struct Text *text);
void sort_sents(struct Text *text);
void delete_sents(struct Text *text);
void print_words(struct Text *text, wchar_t *s);