#ifndef STRUCTURES_H
#define STRUCTURES_H

typedef struct
{
    char* chars;
    size_t size;
} Sentence;


typedef struct
{
    Sentence* sentence;
    size_t size;
} Text;

#endif
