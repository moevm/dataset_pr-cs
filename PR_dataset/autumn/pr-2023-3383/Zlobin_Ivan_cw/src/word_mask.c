#include "word_mask.h"

int match(wchar_t *str, wchar_t *mask) {
    for (int i=0;i<wcslen(str); ++i) {
        if (mask[i]==L'*') {
            if(mask[i+1]==L'\0') return 1;
            for (int j=i;j<wcslen(str); ++j) {
                if (match(str+j,mask+i+1)) return 1;
            }
            return 0;
        } else 
            if(mask[i]!=L'?' && mask[i]!=str[i]) return 0;
    }
    return 1;
}

void word_mask(struct Text *text, wchar_t *mask){
    int i=0;
    int *arr=calloc(text->num_of_sent, sizeof(int));
    for(i=0;i<text->num_of_sent; ++i){
        wchar_t *buff=wcsdup(text->sentences[i]->str);
        wchar_t *pt;
        wchar_t *token=wcstok(buff, L" ,.\n", &pt);
        for(;token!=NULL;){
            if(!match(token, mask)){
                arr[i]=1;
                break;
            }
            token=wcstok(NULL, L" ,.\n", &pt);
        }
        free(buff);
    }
    int ch=0;
    for(int j=0;j<text->num_of_sent;++j){
        ch+=arr[i];
    }
    if(ch==text->num_of_sent){
        wprintf(L"Error: введенная маска не соответсвтует ни единому слову.\n");
        for(int i=0;i<text->num_of_sent;++i){
            free(text->sentences[i]->str);
            text->sentences[i]->str=NULL;
        }
        return;
    }
    for(int i=0;i<text->num_of_sent;++i){
        if(arr[i]){
            free(text->sentences[i]->str);
            text->sentences[i]->str=NULL;
        }
    }
}
