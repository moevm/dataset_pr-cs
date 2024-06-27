#include "zero_changer.h"
void zero_changer(struct Text* start){
    int count = start->size;
    wchar_t** txt= start->sentences;
    int del_count =0;
    int flags[count];
    for (int i=0; i<count; i++){
        flags[i] =1;
    }
    for (int i = 0; i<count-1; i++){
        if (flags[i]>0){
            for (int j=i+1; j< count; j++){
                if (wcscasecmp(txt[i], txt[j])==0){
                    //free(txt[j]);
                    del_count++;
                    flags[j] =-1;
                }
            }
        }
    }
    int res = count - del_count;
    wchar_t** finish_txt = (wchar_t**)malloc(res*sizeof(wchar_t*));
    for (int n=0, p=0; p<count;  p++){
        if (flags[p] != -1){
            finish_txt[n] = wcsdup(txt[p]);
            free(txt[p]);
            n++;
        }
        else free(txt[p]);
    }
    start->size = res;
    start->sentences = realloc(start->sentences, res*sizeof(wchar_t*));
    for (int i = 0; i<res; i++){
        start->sentences[i] =wcsdup(finish_txt[i]);
    }
    for (int i =0; i<res; i++){
        free(finish_txt[i]);
    }
    free(finish_txt);
}
