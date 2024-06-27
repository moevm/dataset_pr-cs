#ifndef OUTPUT_REWORKED_TEXT_H
#define OUTPUT_REWORKED_TEXT_H
#include "structs.h"
#include "output-struct-of-text.h"
#include <wchar.h>
#include <stdlib.h>
#include <wctype.h>
int check_empty(struct Sentence reseaching_sentence);
struct Text remove_equial_sentences(struct Text old_text);
struct Text return_reworked_text(struct Text old_text);
#endif