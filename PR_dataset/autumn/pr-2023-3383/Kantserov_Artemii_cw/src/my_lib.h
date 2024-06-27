#ifndef CW_MY_LIB_H
#define CW_MY_LIB_H

#define SIZE 2
#include "struct.h"

void free_memory_in(struct text* text);
int del_repeat(struct text* text, struct sentence* sentence);
void processing_text(struct text* text);
void free_memory(struct text* text);
int compare_in_text(const struct sentence *f, const struct sentence *s);
int compare_in_sentence(const void* a, const void* b);
void processing_sentence (struct sentence* sentence);
int* correct_date(char* token);

#endif //CW_MY_LIB_H
