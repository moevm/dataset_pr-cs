#include <stdlib.h>
#include <wctype.h>
#include <wchar.h>

wchar_t** get_separators(wchar_t *sentence) { 
    wchar_t** separators = (wchar_t**)calloc(100, sizeof(wchar_t*)); 
    int num_separators = 0; 
    for (int i = 0; i < 100; i++) { 
        separators[i] = (wchar_t*)calloc(100, sizeof(wchar_t)); 
    } 
    int separator_index = 0; 
    for (int i = 0; sentence[i] != L'.'; i++) { 
        if (iswspace(sentence[i]) || sentence[i]== L'.' || sentence[i]== L',') { 
            separators[num_separators][separator_index++] = sentence[i]; 
        } else if (separator_index > 0) { 
            separators[num_separators][separator_index] = L'\0'; 
            num_separators++; 
            separator_index = 0; 
        } 
    } 
    separators[num_separators][separator_index] = L'\0'; 
    num_separators++; 
    separators[num_separators] = NULL; 
    return separators; 
} 