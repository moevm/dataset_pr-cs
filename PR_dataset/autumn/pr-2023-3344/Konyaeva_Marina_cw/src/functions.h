#pragma once
#include "library.h"

void changeEnding(struct Text t);
void moreTen(struct Text *t);
int cmp(const void* sent1,const void* sent2);
int greenWord(struct Text t);
int check(int i,wchar_t*** words,wchar_t* token,struct Text t);
wchar_t ***arrofwords(struct Text t);
wchar_t ***arrofseps(struct Text t);
void freeText(struct Text t);
void func6(struct Text t);
