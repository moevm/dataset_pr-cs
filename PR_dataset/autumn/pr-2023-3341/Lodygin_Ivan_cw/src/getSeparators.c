#include <stdlib.h>
#include <wctype.h>
#include <wchar.h>

wchar_t** getSeparators(wchar_t *sentence) { 
    wchar_t** separators = (wchar_t**)calloc(100, sizeof(wchar_t*)); 
    int numSeparators = 0; 
    for (int i = 0; i < 100; i++) { 
        separators[i] = (wchar_t*)calloc(100, sizeof(wchar_t)); 
    } 
    int separatorIndex = 0; 
    for (int i = 0; sentence[i] != L'.'; i++) { 
        if (iswspace(sentence[i]) || sentence[i]== L'.' || sentence[i]== L',') { 
            separators[numSeparators][separatorIndex++] = sentence[i]; 
        } else if (separatorIndex > 0) { 
            separators[numSeparators][separatorIndex] = L'\0'; 
            numSeparators++; 
            separatorIndex = 0; 
        } 
    } 
    separators[numSeparators][separatorIndex] = L'\0'; 
    numSeparators++; 
    separators[numSeparators] = NULL; 
    return separators; 
} 