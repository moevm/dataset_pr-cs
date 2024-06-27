#ifndef STRUCTS_H
#define STRUCTS_H

typedef struct Sentence
{
    wchar_t *sent;
    int len;
    int size;
} SNT;

typedef struct Text
{
    SNT **sents;
    int len;
    int size;
} TEXT;

#endif