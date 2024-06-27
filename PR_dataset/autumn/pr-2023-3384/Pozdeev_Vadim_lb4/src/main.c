#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int cmp1(const void * s1, const void * s2){
    return strcmp( *(const char **)s1, *(const char **)s2 );
}

int cmp2(const void* s1, const void* s2) {
    return strcmp((const char*) s1, *(const char**) s2);
}

int main(){
    char text[1000+1];
    char str[30+1];
    fgets(text, 1001, stdin);
    scanf("%s", str);
    int len = 0;
    char * text_split[1000];
    char *split = strtok(text, " .");
    for(;split!=NULL;len++){
        text_split[len]=split;
        split=strtok(NULL, " .");
    }
    qsort(text_split, len, sizeof(char *), cmp1);
    if((char **)bsearch(str, text_split, len, sizeof(char *), cmp2)!= NULL ){ printf("exists"); }
    else{ printf("doesn't exist"); }
    return 0;
}

