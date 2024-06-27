#include "structs.h"
#include "third_function.h"

int latin_counter(struct Sentence *sen){
    int lat = 0;
    wchar_t *str = sen->str;
    for (int i = 0; str[i]!= L'\0'; i++){
        if (towlower(str[i]) >= L'a' && towlower(str[i]) <= L'z'){
            lat ++;
        }
    }
    return lat;
}

int cmp_latin_counter(const void *sen1, const void *sen2){
    return latin_counter(*(struct Sentence**) sen2) - latin_counter(*(struct Sentence**) sen1);
}

void latin_sort(struct Text *text){
    qsort(text->sents, text->n, sizeof(struct Sentence*), cmp_latin_counter);
}
