#include "my_lib.h"

struct Text input_text(){
    struct Text text={.cnt_sen=0};
    text.txt = (struct Sentence*)malloc(sizeof(struct Sentence)*BLOCK);
    if(text.txt == NULL)error(2);
    int mem_txt = BLOCK;
    for(;;){
        struct Sentence iter = input_sen();
        if(iter.cnt_ch == 0)break;
        if(mem_txt <= text.cnt_sen+1){
            mem_txt+=BLOCK;
            text.txt = realloc(text.txt,sizeof(struct Sentence)*mem_txt);
            if(text.txt == NULL)error(2);
        }
        int flag =1;
        for(int i=0;i<text.cnt_sen;++i)if(wcscasecmp(text.txt[i].snt,iter.snt)==0)flag =0;
        if(flag)text.txt[text.cnt_sen++]=iter;
        if(iter.snt[wcslen(iter.snt)-1]!= L'.')break;
    }
    return text;
}
