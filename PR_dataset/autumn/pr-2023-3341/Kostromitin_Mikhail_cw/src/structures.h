 #pragma once
 #include <wchar.h>


 typedef struct Sentence
{
    wchar_t* sentence;
    int sizeOfBuf;
    int len;
} Sentence;

typedef struct Text
{
    Sentence* sentences;
    int size;
    int sizeOfBuf;
} Text;