#pragma once
#include "sentence.h"

typedef struct Text
{
    Sentence **sentences;
    int len;
    int cap;
} Text;

Text *create_text();
void extend_text(Text *text);
void free_text(Text *text);
void push_text(Text *text, Sentence *sentence);
void print_text(Text *text);
void work_with_words_and_seps_text(Text *text);
void polindrom(Text *text);

