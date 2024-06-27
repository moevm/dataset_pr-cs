#include <wchar.h>

int doubleEn(wchar_t *sentence) {
    int checkbox = 0;
    for(int i = 0; i < wcslen(sentence)-1; i++) {
        if((sentence[i] == L'\n')&&(sentence[i+1] == L'\n')) {
            checkbox = 1;
        }
    }
    return checkbox;
}