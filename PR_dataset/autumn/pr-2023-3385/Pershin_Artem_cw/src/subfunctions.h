#pragma once

#include "structs.h"
#include <wchar.h>


int sencmp(struct Sentence s1, struct Sentence s2);
void copywordfunc1(struct Word* a, struct Word* b);
int cmpfunc2(const void* a, const void* b);
int checkwordfunc3(wchar_t* word);
void printspecialwordfunc3(struct Word word);
void func4word(struct Word word);