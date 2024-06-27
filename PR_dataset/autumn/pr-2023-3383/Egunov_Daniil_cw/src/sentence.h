#ifndef CW_SENTENCE_H
#define CW_SENTENCE_H

#include <wchar.h>
#include "token.h"

struct Sentence;
typedef struct Sentence Sentence;

Sentence *Sentence_create();

void Sentence_destroy(Sentence *sentence);

size_t Sentence_get_tokens_count(Sentence *sentence);

Token *Sentence_get_token(Sentence *sentence, size_t index);

void Sentence_set_token(Sentence *sentence, Token *token, size_t index);

Sentence *Sentence_append_token(Sentence *sentence, Token *token);

Sentence *Sentence_extend(Sentence *sentence, size_t extension_token_count);

Sentence *Sentence_optimize_size(Sentence *sentence);

size_t Sentence_count_word_occurrences(Sentence *sentence, wchar_t *word);

Sentence *Sentence_color_word(Sentence *sentence, wchar_t *word, wchar_t *color_text);

int Sentence_word_count_compare(const void *a, const void *b);

#endif //CW_SENTENCE_H
