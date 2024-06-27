#pragma once

#define MIN_VECTOR_SIZE 4
#include <stddef.h>

typedef struct Sentence {
    unsigned int len;
    unsigned int allocated;
    unsigned int words;
    float avglen;
    wchar_t body[];
} String;

typedef struct Text {
    unsigned int len;
    unsigned int allocated;
    String* body[];
} Text;

String* new_string(unsigned int _size);
String* extend_string(String* _str);
void append_wchar(Text* _text, wchar_t _ch);
void clear(String** _str);

Text* new_text(unsigned int _size);
Text* extend_text(Text* _text);
void append_new_string(Text** _text);
String** last_string(Text* _text);

void free_text(Text* _text);
