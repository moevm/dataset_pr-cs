#include <stdlib.h>
#include <wchar.h>

wchar_t* wordSymbolChanger(wchar_t *word) { 
    wchar_t* new_word = (wchar_t*)calloc(wcslen(word)+1, sizeof(wchar_t));
    new_word[0] = word[0]; 
    wchar_t prev_symbol = new_word[0]; 
    int count = 1; 
    for(int i = 1; word[i]!= L'\0'; i++) { 
        if(word[i] != prev_symbol) { 
            new_word[count] = word[i]; 
            count++; 
        } 
        prev_symbol = word[i]; 
    } 
    new_word[count] = L'\0';
    return new_word;  
}