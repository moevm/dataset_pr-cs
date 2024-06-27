#pragma once

#include <stdlib.h>
#include <ctype.h>

#include "mystruct.h"

void mydelete(Text* text);

void myfreesentence(Sentence* sentence);

void myfreetext(Text* text);

void mycheckerror(const void* p, char* func, char* var, char* alloctype);

int mygethour(const Sentence* sen, const int start, int* hour);

int mygetminute(const Sentence* sen, const int start, int* minute);

int myisupper(wchar_t c);

int myiscyrillic(wchar_t c);

int countcir(Sentence* sentence);

int compare (const void* a, const void* b);