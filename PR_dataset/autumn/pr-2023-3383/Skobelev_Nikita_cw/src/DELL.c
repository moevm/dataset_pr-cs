#include "my_lib.h"

void del(struct Text* text){
    int cnt = 0, iter =0;
    for(int i=0;i<text->cnt_sen;++i){
        if(text->txt[i].cnt_wrd<=2){
            free(text->txt[i].snt);
            cnt++;
        }
        else text->txt[iter++]=text->txt[i];
    }
    text->cnt_sen-=cnt;
    text->txt = realloc(text->txt,sizeof(struct Sentence)*(text->cnt_sen));
    for(int i=0;i<text->cnt_sen;++i){
    wprintf(L"%S %d\n",text->txt[i].snt,text->txt[i].cnt_wrd);
    }
}
