#ifndef CW_STRUCTS_H
#define CW_STRUCTS_H

#include <wchar.h>

typedef struct{
    wchar_t* chars;
    int count;
    int letters_count;
} Word;
typedef struct{
    wchar_t* chars;
    int size;
} Sentence;
typedef struct{
    Sentence* sentences;
    int size;
} Text;

#endif
