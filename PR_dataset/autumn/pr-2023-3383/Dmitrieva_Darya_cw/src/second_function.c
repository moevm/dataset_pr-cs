#include "structs.h"
#include "second_function.h"

int replace_special_symbol(struct Sentence *sen){
    wchar_t *special_symbol = L">special symbol<";
    wchar_t *str = sen->str;
    wchar_t *new_str = malloc((sen->size + 1) * sizeof(wchar_t));
    new_str[0] = L'\0';
    size_t size = sen->size;
    for (int i=0; str[i]!=L'\0'; i++){
        if (iswpunct(str[i])){
            wchar_t *tmp;
            size += 16;
            tmp = realloc(new_str, (size + 5) * sizeof(wchar_t));
            new_str = tmp;
            wcscat(new_str, special_symbol);
        }
        else{
            wchar_t tmp[2] = {str[i], L'\0'};
            wcscat(new_str, tmp);
        }
    }
    new_str[wcslen(new_str)] = L'\0';
    wprintf(L"%ls", new_str);
    free(new_str);
    return 0;
}

int replace_special_symbol_analys(struct Text *text){ 
    for (int i = 0; i < text->n; i++) { 
        replace_special_symbol(text->sents[i]);
    }
    return 0;
}
