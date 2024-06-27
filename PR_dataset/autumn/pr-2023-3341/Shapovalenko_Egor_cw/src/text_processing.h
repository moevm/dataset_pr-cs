#include <stdlib.h>
#include <wctype.h>
#include <time.h>
#include "structures.h"

struct Text split_text(wchar_t *text_buffer, int len);

void delete_extra_commas(struct Text *text);

void delete_extra_lines(struct Text *text);

void delete_extra_spaces(struct Text *text);

void delete_extra_separators(struct Text *text);

wchar_t* make_lowercase_copy(struct Sentence sentence);

struct Text delete_repeating_sentences(struct Text *text);

int check_format(struct Sentence sentence, int index, int minute_flag);

int **make_time_and_sentence_num_arr(struct Text *text, int *size);

void delete_uppercase_letters(struct Text *text);

int compare(const void * a, const void * b);

void sort_by_cyrillic_symbol_count(struct Text *text);

struct Text delete_sentences_without_special_symbols(struct Text *text);

int add_word(struct Sentence *new_sentence, struct Sentence sentence, int tmp_word_len, int word_len, int *allocated_memory, int *new_len, int tmp_word_index);

struct Text replace_long_words(struct Text *text);