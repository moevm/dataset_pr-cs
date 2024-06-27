#include <wchar.h>
#include <stdlib.h>
#include <wctype.h>
#include "structures.h"

int is_palindrome(wchar_t* str){
    int i = 0;
    int j = wcslen(str) - 1;
    while (i < j){
        if (str[i] != str[j]) return 0;
        i++;
        j--;
    }
    return 1;
}

void func9(Text* text){
    for(int i = 0;i < text->count;i++){
        if(text->sentences[i].str != NULL){
            wchar_t* copy = (wchar_t*) calloc(1000,sizeof(wchar_t));
            int q = 0;
            for (int j = 0; j < wcslen(text->sentences[i].str);j++){
                if (iswalpha(text->sentences[i].str[j])|| iswdigit(text->sentences[i].str[j])){
                    copy[q] = towlower(text->sentences[i].str[j]);
                    q++;
                }
            }
            if (is_palindrome(copy)){
                wprintf(L"%ls\n", text->sentences[i].str);
            }
        }
    }
}
