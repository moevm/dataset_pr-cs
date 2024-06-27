#include <wchar.h>
#include <wctype.h>

int cmpSents(wchar_t *first_sent, wchar_t *second_sent) {
    int checkbox = 0;
    if(wcslen(first_sent) != wcslen(second_sent)) {
        checkbox = 0;
    } else{
        for(int i = 0; i < wcslen(first_sent); i++) {
            if(towupper(first_sent[i]) != towupper(second_sent[i])) {
                checkbox = 0;
                break;
            } else checkbox = 1;
        }
    }
    return checkbox;
}