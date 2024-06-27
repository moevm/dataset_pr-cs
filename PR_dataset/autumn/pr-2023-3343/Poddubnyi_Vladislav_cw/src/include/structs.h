//
// Created by rect on 17.11.2023.
//

#ifndef CW_STRUCTS_H
#define CW_STRUCTS_H

#include <wchar.h>

typedef struct{
    wchar_t* chars;
    int size;
}Sentence;

typedef struct{
    Sentence* sentences;
    int size;
}Text;

typedef struct{
    wchar_t* chars;
    int* occurrences;
    int occurrencesSize;
} Word;


#endif //CW_STRUCTS_H
