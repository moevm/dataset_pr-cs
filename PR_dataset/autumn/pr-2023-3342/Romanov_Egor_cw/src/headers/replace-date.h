#ifndef REPLACE_DATE_H
#define REPLACE_DATE_H
#include <wchar.h>
#include <wctype.h>
#include <stdlib.h>
#include <locale.h>
#include "split-sentences-on-words.h"
#include "structs.h"
#include "output-struct-of-text.h"
#include "return-reworked-text.h"
#include "free-text.h"
wchar_t *find_year(struct Sentence sentence, wchar_t *month);
wchar_t *find_day(struct Sentence sentence, wchar_t *month);
wchar_t *month_to_num(wchar_t *month, wchar_t **months);
int find_start_of_date(struct Sentence sentence, wchar_t *month);
void replace(struct Sentence sentence);
void replace_date(struct Text text);
#endif