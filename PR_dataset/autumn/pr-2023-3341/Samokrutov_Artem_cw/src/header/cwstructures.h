#ifndef CWSTRUCTURES_H
#define CWSTRUCTURES_H


#include <stdio.h>
#include <wchar.h>

#include "cwerror.h"

typedef struct {
	wchar_t *characters;
	int len;
	int first_word_len;
} Sentence;

typedef struct {
	Sentence *sentences;
	int len;
} Text;

void fill_len(Text *);

void fill_first_word_len(Text *);

void Sentence_cpy(Sentence *, Sentence *);

void delete_Sentence(Text *, int);

void free_Text(Text *);


#endif
