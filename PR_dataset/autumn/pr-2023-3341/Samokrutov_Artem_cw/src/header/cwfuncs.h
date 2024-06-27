#ifndef CWFUNCS_H
#define CWFUNCS_H


#include <stdlib.h>
#include <wchar.h>

#include "cwerror.h"
#include "cwio.h"
#include "cwprocessing.h"
#include "cwstructures.h"

#define YEAR_OFFSET 1900
#define MIN_ALLOWED_WORD_LEN 4


Text *preprocess_Text(void);

int count_words(Sentence);

int max_word_len(Sentence);

void date(Sentence);

void dateify(Text *);

void reverse_part(wchar_t *, int, int);

void reverse_each_word(wchar_t *);

void reverse_word_order(wchar_t *);

void reverse_Text(Text *);

int first_word_len_cmp(const void *, const void *);

void sort_by_first_word_len(Text *);

int words_are_too_short(Sentence);

void print_Sentences_with_short_words(Text *);

int is_palindrome(wchar_t *);

void print_palindromes(Text *);

void task_match(Text *, int);


#endif
