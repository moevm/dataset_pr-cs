#include "mask_input.h"
#define BLOCK_SIZE 8

wchar_t* mask_input(void){
    wchar_t *mask=malloc(sizeof(wchar_t)*BLOCK_SIZE);
    wchar_t sim=getwchar();
    int i=0;
    for(;1;sim=getwchar(), ++i){
        if(i==0 && sim==L'\n'){
            --i;
            continue;
        }
        if(iswspace(sim) || sim==L','){
            mask[i]=L'\0';
            break;
        }
        mask[i]=sim;
        if(i%BLOCK_SIZE==BLOCK_SIZE-2){
            mask=realloc(mask, sizeof(wchar_t)*(i+BLOCK_SIZE));
        }
    }
    mask=realloc(mask, sizeof(wchar_t)*wcslen(mask));
    return mask;
}