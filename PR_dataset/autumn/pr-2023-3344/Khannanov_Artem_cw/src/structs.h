#include <wchar.h>

#ifndef STRUCTS_H
#define STRUCTS_H


struct Sentence { // Структура предложения
    wchar_t *sentence;
};


struct Text { // Структура текста
    struct Sentence *text;
    int count;
    int is_memory_ok;
};


#endif