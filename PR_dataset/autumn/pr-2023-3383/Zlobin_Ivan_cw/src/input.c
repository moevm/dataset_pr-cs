#include "input.h"
#define STEP 8

int repeat_check(struct Text *text){
    for(int i=0;i<text->num_of_sent;++i){
        if(text->sentences[i]->len==text->sentences[text->num_of_sent]->len){
            int ch=1;
            for(int j=0;j<text->sentences[i]->len;++j){
                if(towlower(text->sentences[i]->str[j])!=towlower(text->sentences[text->num_of_sent]->str[j])){
                    ch=0;
                    break;
                }
            }
            if(ch) return 0;
        }
    }
    return 1;
}

struct Text input(void){
    struct Text text;
    text.sentences=malloc(STEP*sizeof(struct Sentence*));
    text.num_of_sent=0; int i=0;
    int check=1;
    for(;1;){
        text.sentences[text.num_of_sent]=malloc(sizeof(struct Sentence));
        text.sentences[text.num_of_sent]->str=malloc(STEP*(sizeof(wchar_t)));
        text.sentences[text.num_of_sent]->len=STEP;
        wchar_t sim=getwchar();
        for(i=0;;sim=getwchar(),++i){
            //проверка лишней табуляции в начале предложения
            if(i==0 && iswspace(sim)){
                if(sim==L'\n' && !check) break;
                if(sim==L'\n' && check) {check=0;}
                --i;
                continue;}
            text.sentences[text.num_of_sent]->str[i]=sim;
            //завершение ввода предложения
            if(text.sentences[text.num_of_sent]->str[i]==L'.'){
                text.sentences[text.num_of_sent]->str[i+1]=L'\n';
                text.sentences[text.num_of_sent]->str[i+2]=L'\0';
                check=1;
                break;
            }
            //перевыделение памяти для предложения
            if(i==text.sentences[text.num_of_sent]->len-3){
                text.sentences[text.num_of_sent]->len+=STEP;
                text.sentences[text.num_of_sent]->str=realloc(text.sentences[text.num_of_sent]->str, sizeof(wchar_t)*text.sentences[text.num_of_sent]->len);
            }
        }
        //завершение ввода текста
        if(!check){
            free(text.sentences[text.num_of_sent]->str);
            free(text.sentences[text.num_of_sent]);
            text.sentences=realloc(text.sentences, sizeof(struct Sentence*)*text.num_of_sent);
            break;
        }
        //окончательное перевыделение памяти для предложения
        text.sentences[text.num_of_sent]->len=wcslen(text.sentences[text.num_of_sent]->str);
        text.sentences[text.num_of_sent]->str=realloc(text.sentences[text.num_of_sent]->str, sizeof(wchar_t)*(text.sentences[text.num_of_sent]->len+1));
        //проверка на повторы
        if(repeat_check(&text)){
            text.num_of_sent+=1;
        }
        else{
            free(text.sentences[text.num_of_sent]->str);
            free(text.sentences[text.num_of_sent]);
        }
        //перевыделение памяти для указателей на предложения
        if(text.num_of_sent%STEP==STEP-1){
            text.sentences=realloc(text.sentences,(text.num_of_sent+STEP)*sizeof(struct Sentence*));
        }
    }
    return text;
}
