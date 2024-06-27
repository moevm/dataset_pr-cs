#ifndef STRUCTURES_H
#define STRUCTURES_H

#include <wchar.h>

typedef struct{
    wchar_t* chars;
    int size;
    int amofwords;
}Sentence;

typedef struct{
    Sentence* sentences;
    int size;
}Text;
 
#endif //STRUCTURES_H