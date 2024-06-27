#pragma once

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<wchar.h>
#include<time.h>
#include<wctype.h>

#define MEMORY_STEP 100
#define SENTENCE_SEP L".\n"
#define WORD_SEP L" ,"

#ifndef TEXT_STRUCT
#define TEXT_STRUCT
typedef struct Word{
    wchar_t * chars;
    wchar_t sep;
    size_t len;
} Word;
typedef struct Sentence{
    Word* words;
    size_t len;
} Sentence;
typedef struct Text{
    Sentence* sents;
    size_t len;
} Text;
#endif

void removeEmptySentences(Text* text);
void removeCopies(Text* text);
void removeSentence(int i, Text* text);
void freeSentence(Sentence sent);
void freeText(Text* text);
void changeWords(Text* text, Word replaceFrom, Word replaceTo);
void sortSentences(Text* text);
void changeVowels(Text *text);
void countSymbols(Text *text);
