#include "my_lib.h"

int cmp_low(const void* first, const void* second){
    struct Sentence f= *(struct Sentence*)first;
    struct Sentence s= *(struct Sentence*)second;
    if(f.cnt_wrd<s.cnt_wrd)return 1;
    else return 0;
}


void sort_low_cnt_wrd(struct Text*text){
    qsort(text->txt,text->cnt_sen,sizeof(struct Sentence),cmp_low);
    for(int i=0;i<text->cnt_sen;++i){
        wprintf(L"%S\n",text->txt[i].snt);
    }
}
