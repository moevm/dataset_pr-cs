#pragma once

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<wchar.h>

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

Word readWord();
Sentence readSentence();
Text readText();
void printText(Text);
void printAnagrams(Text);
