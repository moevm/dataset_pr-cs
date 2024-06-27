#include "up_changer.h"
void up_changer(struct Text* start){
    wchar_t** start_text = start->sentences;
    int del_size = 0;
    int flag = 0;
    int count = start->size;
    int delete_flags[count];
    for (int i =0; i<count; i++){
        delete_flags[i] = 1;
    }
    for (int i = 0; i< count; i++){
        wchar_t* sent = start_text[i];
        flag = 0;
        if (iswupper(sent[0]) == 0){
            for (int j =1; j<wcslen(sent); j++){
                if ((sent[j-1] == L' ' || sent[j-1] == L',' || sent[j-1] == L'\n') && (iswupper(sent[j]) != 0)){
                    flag = 1;
                    break;
                }
            }
        }
        else{
            flag = 1;
        }
        if (flag ==0){
            del_size++;
            free(start_text[i]);
            delete_flags[i] = -1;
        }
    }
    int res = count - del_size;
    wchar_t** finish_text = malloc(res*sizeof(wchar_t*));
    for (int n=0, p=0; n<count-del_size, p<count;  p++){
        if (delete_flags[p] != -1){
            finish_text[n] = wcsdup(start_text[p]);
            free(start_text[p]);
            n++;
        }
    }
    start->size = count-del_size;
    start->sentences = realloc(start->sentences, res*sizeof(wchar_t*));
    for (int i = 0; i<res; i++){
        start->sentences[i] =wcsdup(finish_text[i]);
    }
    for (int i = 0; i<res; i++){
        free(finish_text[i]);
    }
    free(finish_text);
}
