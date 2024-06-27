#include "my_lib.h"

struct Sentence input_sen(){
    struct Sentence sen={.cnt_wrd=0,.cnt_ch=0};
    int mem_cnt=BLOCK;
    sen.snt = (ch*)malloc(sizeof(ch)*BLOCK);
    if(sen.snt == NULL)error(2);
    int flag_null = 0;
    int flag_tab = 0;
    for(ch c = getwchar();;c = getwchar()){
        if(mem_cnt <= sen.cnt_ch+2){
            mem_cnt += BLOCK;
            sen.snt = realloc(sen.snt,sizeof(ch)*mem_cnt);
            if(sen.snt == NULL)error(2);
        }
        if(c == L'\n'){
            flag_null++;
            if(flag_null == 2){
                sen.snt[sen.cnt_ch]=L'\0';
                return sen;
            }
            continue;
        }
        if(c ==  L'.'){
            sen.snt[sen.cnt_ch++]=L'.';
            sen.snt[sen.cnt_ch]=L'\0';
            return sen;
        }
        if(c == L' ' || c == L','){
            flag_tab++;
            if(sen.cnt_wrd ==0)continue;
        }else if(flag_tab !=0 || sen.cnt_wrd == 0){
            sen.cnt_wrd++;
            flag_tab=0;
        }
        flag_null = 0;
        sen.snt[sen.cnt_ch++]=c;
    }
}
