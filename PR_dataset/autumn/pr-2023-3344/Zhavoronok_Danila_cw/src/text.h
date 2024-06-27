#pragma once
#include "sentence.h"
typedef struct Text
{
    sentence **sentences;
    int length;
    int capacity;
} text;

void init_text(text *txt);
text *create_text();
void free_text(text *txt);
void enlarge_text(text *txt);
void append_text(text *txt, sentence *str);
void print_text(text *txt);
sentence *find_sentence_in_text(text *, sentence *, int is_case_sensitive);
