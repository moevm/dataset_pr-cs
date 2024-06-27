#ifndef TEXTFUNCS_H
#define TEXTFUNCS_H
#include"sentfuncs.h"
#include"output.h"
#include"input.h"
#include"structures.h"
#include"memfuncs.h"
struct Text primaryProcessing(struct Text txt);
void printAllAnagramms(struct Text* txt);
void sortByUpperLetters(struct Text* txt);
void replaceVowels(struct Text* txt);
void replaceWordToKey(struct Text* txt);
void menu();
void func9(struct Text* txt);
#endif

