#ifndef READ_TEXT_HEADER
#define READ_TEXT_HEADER

#include <wchar.h>
#include <wctype.h>
#include <stdlib.h>
#include "structs.h"
#include "failure.h"

#define SYMBOL_NEW_LINE L'\n'
#define SYMBOL_END_STRING L'\0' 
#define SYMBOL_POINT L'.'
#define SYMBOL_SPACE L' '

wchar_t * read();
Sentence * text_to_sentence(wchar_t * text, size_t start_index);
int compare_for_text_sentences(const wchar_t * first_sentence, const wchar_t * second_sentence);
int is_dublicate(Text* text, Sentence* string);
Text * read_text();

#endif
