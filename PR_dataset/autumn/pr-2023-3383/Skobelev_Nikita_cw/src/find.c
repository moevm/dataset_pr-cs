#include "my_lib.h"

void find_(struct Text* text){
    for(int i=0;i<text->cnt_sen;++i){
        ch* str =wcsdup(text->txt[i].snt);
        ch* iter;
        ch* it = malloc(sizeof(ch)*text->txt[i].cnt_ch);
        if(it == NULL)error(2);
        ch *pt;
        iter = wcstok(str,L" ,.",&pt);
        while(iter!=NULL){
            it = iter;
            iter = wcstok(NULL,L" ,.",&pt);
        }
        ch*find_st = wcsdup(text->txt[(i+1)%(text->cnt_sen)].snt);
        if(find_st == NULL)error(2);
        int flag = 0;
        ch red_start[] = L"\033[1;31m";ch red_end[] = L"\033[1;0m";
        int step = wcslen(it);
        for(iter = wcsstr(find_st,it);iter!=NULL;iter = wcsstr(iter+1,it)){
            if((find_st-iter)==0||*(iter-1)==' ' || *(iter-1)==','){
                    if(find_st+wcslen(find_st) == iter+step || *(iter+step)==' ' || *(iter+step)==','||*(iter+step)=='.'){
                        flag = 1;
                        while(find_st!=iter){
                            wprintf(L"%c",*find_st);
                            ++find_st;
                        }
                        wprintf(L"%S",red_start);
                        for(int i=0;i<step;++i){
                            wprintf(L"%c",*(find_st+i));
                        }
                        find_st+=step;
                        wprintf(L"%S",red_end);
                    }
            }
        }
        if(flag){
            for(;*find_st;++find_st)wprintf(L"%c",*find_st);
            wprintf(L"\n");
        }
        free(str);
    }
}
//qwe qwe qwe.
/*qwe. qqwe qwe.
    char s[]="asdf";
    char st[100];
    char red_start[] = "\033[1;31m";
    char red_end[] = "\033[1;0m";
    memcpy(st,s,sizeof(char)*2);
    st[2]='\0';
    char itog [100];
    itog[0]='\0';
    strncat(itog,st,sizeof(char)*2);
    strncat(itog,red_start,sizeof(char)*strlen(red_start));
    memcpy(st,s+2,sizeof(char)*2);
    strncat(itog,st,sizeof(char)*2);
    strncat(itog,red_end,sizeof(char)*strlen(red_end));
    printf("%s",itog);
    */
