#pragma once

#include "structs_libraries.h"

void memory_clean (struct Text *text);
struct Word* create_struct_word (wchar_t *token, int len);
void record_words (struct Text *text);
void delete_sentence (struct Text *text, int numb_of_sent);
void delete_empty_sents (struct Text *text);
void delete_equal_sentences (struct Text *text);
wchar_t* word_to_str (struct Word *word);
int is_digit (wchar_t *str);
int cnt_sum_of_coodes_of_1st_word (struct Sentence *sentence);
int compare_sents (const void *sent_1,const void *sent_2);
void insert_word (wchar_t *sent, int ind, wchar_t *word);
int is_consonant (wchar_t ch);
int word_have_3_consonants (wchar_t *word);
void print_help ();
void output_text (struct Text *text);