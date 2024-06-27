#pragma once
#include "sentence.h"

typedef struct Text
{
    Sentence **array_sentence;
    int length;
    int capacity;
} Text;

void initial_text(Text *txt);
void expand_text(Text *txt);
Text *make_text();
void print_text(Text *txt);
void free_text(Text *txt);