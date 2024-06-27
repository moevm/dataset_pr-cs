#ifndef STRUCTS_H
#define STRUCTS_H

#include <stdlib.h>

typedef struct{
    char *chars;
    size_t size;
} Sentence;

typedef struct{
    Sentence *sentences;
    size_t size;
} Text;

typedef struct{
    char *letters;
    size_t size;
} Word;

#endif
