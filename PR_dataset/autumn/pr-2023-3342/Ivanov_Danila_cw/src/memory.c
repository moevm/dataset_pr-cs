#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <wchar.h>
#include <wctype.h>
#include <locale.h>
#define TEXT_MAX_SIZE 100
#define NUMBER_OF_SENTENCES 10

wchar_t** allocate_memory_for_text(){
    wchar_t **dynamic_strs = malloc(NUMBER_OF_SENTENCES * sizeof(wchar_t*));
    for(int i = 0; i < NUMBER_OF_SENTENCES; i++){
        dynamic_strs[i] = calloc(TEXT_MAX_SIZE, sizeof(wchar_t));
    }
    return dynamic_strs;
}

void free_memory(wchar_t** dynamic_strs, int len){
    for (int i = 0; i < len - 1; i++){
        free(dynamic_strs[i]);
    }
    free(dynamic_strs);
}