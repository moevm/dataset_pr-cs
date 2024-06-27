#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define END_OF_STRING '\0'
int cmp(const void* a, const void* b){
        const char** f = (const char**)a;
        const char** s = (const char**)b;
        return strcmp(*f,*s);
}

int cmp_for_search(const void* key, const void* val){
        const char* k = (const char*)key;
        const char** v = (const char**)val;
        return strcmp(k, *v);
}

char* input(char* text,char* key){
        char symbol = getchar();
        int i = 0, j = 0;
        while(symbol!='\n' && symbol!=EOF){
                text[i++] = symbol;
                symbol = getchar();
        }
        text[i] = END_OF_STRING;
        symbol = getchar();
        while(symbol!='\n' && symbol!=EOF){
                key[j++] = symbol;
                symbol = getchar();
        }
        key[j] = END_OF_STRING;
}

char** split_text(char* text, int* key){
        char** changed_text = (char**)malloc(100*sizeof(char*));
        char* word = strtok(text, " .");
        while(word!=NULL){
                changed_text[*key] = (char*)malloc((strlen(word)+1)*sizeof(char));
                strcpy(changed_text[*key],word);
                (*key)++;
                word = strtok(NULL," .");
        }
        changed_text[*key] = END_OF_STRING;
        return changed_text;
}

void output(char** res){
        if(res!=NULL){
                printf("exists\n");
        }else{
                printf("doesn't exist\n");
        }
}

int main(){
        char* text = (char*)malloc(1000*sizeof(char));
        char* key = (char*)malloc(30*sizeof(char));
        input(text,key);
        int count = 0;
        char** changed_text = (char**)split_text(text,&count);

        qsort(changed_text,count,sizeof(char*),cmp);

        char** res =  bsearch(key,changed_text,count,sizeof(char*),cmp_for_search);

        output(res);

        free(text);
        free(changed_text);
        free(key);
}
