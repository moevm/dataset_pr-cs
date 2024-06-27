#ifndef PALINDROMES_H
#define PALINDROMES_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <wctype.h>
#include <wchar.h>

#include"Struct.h"

int Is_Palindrome(wchar_t *word, int size);
int Check_Sentence(Sentence *sentence);
int Num_Words(Sentence *sentence);
void Palindromes(Text *text);


#endif