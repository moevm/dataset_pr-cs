#ifndef SORT_BY_LENGTH_H
#define SORT_BY_LENGTH_H
#include <stdio.h>
#include <stdlib.h>
#include "structs.h"
#include "output-struct-of-text.h"
#include "split-sentences-on-words.h"
#include "return-reworked-text.h"
#include "free-text.h"
int cmp(const void *a, const void *b);
void sort_by_length(struct Text text);
#endif