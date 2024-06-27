#ifndef DELETE_SPECIAL_SENTENCES_H
#define DELETE_SPECIAL_SENTENCES_H
#include <stdlib.h>
#include <wchar.h> 
#include <wctype.h>
#include "structs.h"
#include "return-reworked-text.h"
int check_numbers(struct Sentence sentence);
int check_special_symbols(struct Sentence sentence);
struct Text delete_special_sentences(struct Text text);
#endif