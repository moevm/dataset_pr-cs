#include "len_of_word.h"

void len_count(struct Text *text){
    for(int i=0; i<text->num_of_sent; ++i){
        int len_of_words=0;
        int cnt=0;
        wchar_t *str=wcsdup(text->sentences[i]->str);
        wchar_t *pt;
        wchar_t *token=wcstok(str, L" ,.\n", &pt);
        for(;token!=NULL; ++cnt){
            len_of_words+=wcslen(token);
            token=wcstok(NULL, L" ,.\n", &pt);
        }
        text->sentences[i]->midlen=(float)len_of_words/(float)cnt;
        text->sentences[i]->cnt=cnt;
        free(str);
    }
}
