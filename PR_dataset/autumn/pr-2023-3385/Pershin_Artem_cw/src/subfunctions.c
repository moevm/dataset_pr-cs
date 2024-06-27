#include "subfunctions.h"

#include "structs.h"

#include <stdio.h>
#include <stdlib.h>
#include <wchar.h>
#include <wctype.h>
#include <locale.h>


int sencmp(struct Sentence s1, struct Sentence s2){
    if(s1.len!=s2.len){
        return 0;
    }
    for(int i=0; i<s1.len; i++){
        if(wcscasecmp(s1.p[i].p,s2.p[i].p)){
            return 0;
        }
    }
    return 1;
}


void copywordfunc1(struct Word* a, struct Word* b){
    int size = wcslen((*a).p) + wcslen((*b).p);
    wchar_t* newp = (wchar_t*)malloc((size + 1) * sizeof(wchar_t));
    if(newp == NULL){
    	printf("Не удалось выделить память");
    	exit(1);
    }
    int k = 0;
    for(int j = 0; j < (*b).len; j++){
        newp[k] = (*b).p[j];
        k++;
    }
    for(int i = (*a).len; (*a).p[i]; i++){
        newp[k] = (*a).p[i];
        k++;
    }
    newp[k] = L'\0';
    free((*a).p);
    (*a).p = newp;
    (*a).len = (*b).len;
}


int cmpfunc2(const void* a, const void* b){
    struct Sentence* f = (struct Sentence*)a;
    struct Sentence* s = (struct Sentence*)b;
    int fc, sc;
    if((*f).len < 3){
        fc = 0;
    }
    else{
        fc = (*f).p[2].len;
    }
    if((*s).len < 3){
        sc = 0;
    }
    else{
        sc = (*s).p[2].len;
    }
    if(fc < sc){
        return -1;
    }
    if(fc > sc){
        return 1;
    }
    return 0;
}


int checkwordfunc3(wchar_t* word){
    unsigned key = 0;
    for(int i = 0; word[i]; i++){
        if(key & 1){
            if(iswdigit(word[i])){
                key++;
            }
        }else{
            if(iswalpha(word[i])){
                key++;
            }
        }
    }
    return (key >= 3);
}


void printspecialwordfunc3(struct Word word){
    printf("\033[0;32m");
    int i = 0;
    while(i < word.len){
        printf("%C", word.p[i]);
        i++;
    }
    printf("\033[0m");
    while(i < wcslen(word.p)){
        printf("%C", word.p[i]);
        i++;
    }
}


void func4word(struct Word word){
    for(int i = 0; i < word.len; i++){
        while(word.p[i] == word.p[i+1]){
            word.len--;
            for(int j = i; word.p[j]; j++){
                word.p[j] = word.p[j+1];
            }
        }
    }
}
