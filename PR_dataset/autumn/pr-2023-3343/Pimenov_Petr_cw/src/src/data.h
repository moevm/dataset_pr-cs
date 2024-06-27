#ifndef DATA_H
#define DATA_H

#include <wchar.h>

typedef struct
{
    wchar_t *data;
    size_t length;
} Sentence;

typedef struct
{
    Sentence *data;
    size_t length;
} Text;

typedef struct
{
    wchar_t *data;
    size_t count;
} WordCount;

#endif
