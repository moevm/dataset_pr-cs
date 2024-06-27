#include "textio.h"

int check_sentence(vector* text, vector* sentence){
    for(size_t i = 0;i<text->size;i++){
        size_t len = ((vector*)(text->data))[i].size;
        if(len == sentence->size && !wcsncasecmp(sentence->data,((vector*)(text->data))[i].data,len))
            return 1;
    }
    return 0;
}

int read_sentence(vector* text){
    vector* sentence = vcreate(sizeof(wchar_t));
    wchar_t buf = 0;
    int f = 1;
    while((buf = getwchar())!=L'.'){
        if(buf==L'\n' && f){
            f++;
        }
        if(f==3){
            vfree(sentence);
            return END_OF_TEXT;
        }
        if(f && iswspace(buf)){
            continue;
        }else{
            f = 0;
        }
        verr(vadd(sentence,&buf));
        if(sentence->size>1 && buf==L'\n' && (((wchar_t*)sentence->data)[sentence->size-2])==L'\n'){
            if(!check_sentence(text,sentence)){
                verr(vresize(sentence,sentence->size-=2));
                wchar_t point = L'.';
                verr(vadd(sentence,&point));
                verr(vadd(text,sentence));
                free(sentence);
            }else
                vfree(sentence);
            return END_OF_TEXT;
        }
    }
    verr(vadd(sentence,&buf));
    if(!check_sentence(text,sentence)){
                verr(vadd(text,sentence));
                free(sentence);
    }else
        vfree(sentence);
    return END_OF_SENTENCE;
    
}

vector* read_text(){
    vector* text = vcreate(sizeof(vector));
    while (read_sentence(text)!=END_OF_TEXT){};
    return text;
}

void print_text(vector *text){
    for(size_t i = 0;i<text->size;i++){
        wchar_t* sentence = ((vector*)(text->data))[i].data;
        size_t len = ((vector*)(text->data))[i].size;
        for(size_t j = 0;j<len;j++){
            putwchar(sentence[j]);
        }
        wprintf(L"\n");
    }
}
