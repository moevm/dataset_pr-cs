#include <wchar.h>
#include <stdlib.h>
#include <string.h>
#include "../include/struct.h"

void replaceSymbol(Sentence* sentence, wchar_t symbol, wchar_t* replace_symbol) {
    wchar_t* current_pos = wcschr(sentence->sentence, symbol);
    int count_replacements = 0;

    while (current_pos) {
        int position = wcslen(sentence->sentence) - wcslen(current_pos);
        
        sentence->size += wcslen(replace_symbol);
        sentence->sentence = (wchar_t*) realloc(sentence->sentence, (sentence->size + 10) * sizeof(wchar_t));

        memmove(sentence->sentence + position + wcslen(replace_symbol) - 1, sentence->sentence + position, (wcslen(sentence->sentence) - position + 1)* sizeof(wchar_t));
        memmove(sentence->sentence + position, replace_symbol, wcslen(replace_symbol) * sizeof(wchar_t));

        current_pos = wcschr(current_pos + wcslen(replace_symbol), symbol);
        count_replacements++;
    }
}