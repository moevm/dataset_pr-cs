#include <stdlib.h>
#include <wchar.h>
#include<wctype.h>
#include<stdio.h>
#include "structures.h"

int palindromSentence(wchar_t *str) {
    wchar_t *tmp1 = (wchar_t *)malloc(sizeof(wchar_t) * (wcslen(str) + 1) );
    wchar_t *tmp2 = (wchar_t *)malloc(sizeof(wchar_t) * (wcslen(str) + 1));

    // Заполнение первой строки в нижнем регистре
    int index = 0;
    for (int i = 0; i < wcslen(str); i++) {
        if (iswalnum(str[i])) {
            tmp1[index++] = towlower(str[i]);
        }
    }
    tmp1[index] = L'\0';

    index = 0;
    for (int i = wcslen(str) - 1; i >= 0; i--) {
        if (iswalnum(str[i])) {
            tmp2[index++] = towlower(str[i]);
        }
    }
    tmp2[index] = L'\0';

    int res = wcscmp(tmp1, tmp2);
    if (res == 0) {
        return 1;
    } else {
        return 0;
    }

    free(tmp1);
    free(tmp2);
}

void palindromInText(struct Text *text){
    for (int i = 0; i < text->len; i++) {
        int res = palindromSentence(text->sentences[i]->sentence);
        if (res == 1)
            wprintf(L"%ls.\n", text->sentences[i]->sentence);
    }
}
