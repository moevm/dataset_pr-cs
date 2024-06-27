#include "func.h"
#define BLOCK_SIZE 8

int check(wchar_t *str1, wchar_t *str2){
    if(wcslen(str1)!=wcslen(str2)) return 0;
    for(int t=0;t<wcslen(str1); ++t){
        if(towlower(str1[t])!=towlower(str2[t]))
            return 0;
    }
    return 1;
}

struct Text sec(){
    wchar_t *str=malloc(sizeof(wchar_t));
    wchar_t sim =getwchar();
    sim = getwchar();
    int len=0;
    int cnt=1;
    for(;1;++len, sim=getwchar()){
        if(sim==L'\n'){
            str[len]=L'\0';
            break;
        }
        if(len>0 && sim==L' ') ++cnt;
        str[len]=sim;
            str=realloc(str, sizeof(wchar_t)*(len+3));
    }
    //wprintf(L"[%d]\n", cnt);
    struct Text text=input();
    wchar_t **words=malloc(sizeof(wchar_t*)*cnt);
    wchar_t *pt;
    wchar_t *token=wcstok(str, L" \n", &pt);
    int i;
    for(i=0;token!=NULL;++i){
        words[i]=wcsdup(token);
        token=wcstok(NULL, L" \n", &pt);
    }
    cnt=i;
    len_count(&text);
    for(i=0;i<text.num_of_sent;++i){
        wchar_t **words1=malloc(sizeof(wchar_t*)*(text.sentences[i]->cnt+1));
        wchar_t *buff=wcsdup(text.sentences[i]->str);
        wchar_t *pt;
        wchar_t *token=wcstok(buff, L" ,.\n", &pt);
        int j;
        for(j=0;token!=NULL;++j){
            words1[j]=wcsdup(token);
            token=wcstok(NULL, L" ,.\n", &pt);
        }
        int cnt1=j;
        free(buff);
        int ch=1;
        for(j=0;j<text.sentences[i]->cnt;++j){
            ch=1;
            for(int w=0;w<cnt;++w){
                if(!check(words1[j], words[w])){
                    ch=0;
                }
                else{
                    ch=1;
                    break;
                }
            }
            if(!ch){
                free(text.sentences[i]->str);
                text.sentences[i]->str=NULL;
                break;
            }
        }
        for(j=0;j<cnt1;++j){
            free(words1[j]);
        }
        free(words1);
    }
    for(i=0;i<cnt;++i){
        free(words[i]);
    }
    free(words);
    free(str);
    return text;
}