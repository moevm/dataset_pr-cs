#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <wchar.h>
#include <wctype.h>
#include <locale.h>
#include <ctype.h>
#include "Struct.h"

#define size_block 50

void help();

void freememory(struct Text* text);
void delSentence(struct Text* text, int id);

void delDuplicate(struct Text* text);

int len_translit_char(struct Sentence* a, int i);
int translit_char(wchar_t* str, int i, int size);
int translit_sentence(struct Sentence* a);
void translit_text(struct Text* text); 

struct Sentence* search_special_char(struct Sentence* a); 
int comp_special_char(const void* a, const void* b);
struct Text* search_special_char_text(struct Text* text); 

int translit_dig(wchar_t *str, int i, int size);
int len_bin(struct Sentence* a, int i);
int translit_sentence_dig(struct Sentence* a); 
void translit_text_bin(struct Text* text);

int odd_sen(struct Sentence* a);
void del_odd_sen(struct Text* text);
