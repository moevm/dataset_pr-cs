#pragma once
#include <stdio.h>
#include <locale.h>
#include <wchar.h>
#include <wctype.h>
#include <stdlib.h>
#include <stddef.h>
#include <stdbool.h> 
#include <string.h>
#define STEP 10

struct Sentence {
    wchar_t* str; 
    int size;
};
struct Text {
    struct Sentence** sents; 
    int n;                   
    int size;                
    bool shouldFree; // Флаг для определения, следует ли освобождать память
};
