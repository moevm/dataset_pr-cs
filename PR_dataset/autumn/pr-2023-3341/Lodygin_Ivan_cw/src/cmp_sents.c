#include <wchar.h>
#include <wctype.h>

int cmp_sents(wchar_t *first_sentence, wchar_t *second_sentence) {
    int checkbox = 0;
    if(wcslen(first_sentence) != wcslen(second_sentence)) {
        checkbox = 0;
    } else{
        for(int i = 0; i < wcslen(first_sentence); i++) {
            if(towupper(first_sentence[i]) != towupper(second_sentence[i])) {
                checkbox = 0;
                break;
            } else checkbox = 1;
        }
    }
    return checkbox;
}