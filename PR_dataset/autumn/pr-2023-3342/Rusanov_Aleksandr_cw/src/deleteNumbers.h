#ifndef DELETE_NUMBERS_H
#define DELETE_NUMBERS_H
#include <wchar.h>
#include <stdlib.h>
#include <wctype.h>
#include <string.h>
#include "textHandle.h"
#include "struct.h"


int isNumber(const wchar_t *word);
wchar_t *remove_nubmers_from_sentence(Sentence sentence);
void delete_numbers_from_text(Text text);


#endif
