#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_LEN_TEXT 1000
#define MAX_LEN_STR 30

int qs_cmp(const void* a, const void* b) {
    const char** f = (const char**)a;
    const char** s = (const char**)b;
    return strcmp(*f, *s);
}

int bs_cmp(const void* key, const void* val) {
    const char* k = (const char*)key;
    const char** v = (const char**)val;
    return strcmp(k, *v);
}

int main() {
    char text[MAX_LEN_TEXT + 1];
    char str[MAX_LEN_STR + 1];
    fgets(text, MAX_LEN_TEXT, stdin);
    fgets(str, MAX_LEN_STR, stdin);
    for(int i = 0; i < strlen(text); i++){
        if(text[i] == '\n'){
            text[i] = '\0';
            break;
        }
    }
    for(int i = 0; i < strlen(str); i++){
        if(str[i] == '\n'){
            str[i] = '\0';
        }
    }
    char* word;
    word = strtok(text, " .");
    char** new_text = (char**)malloc(sizeof(char*) * MAX_LEN_TEXT);
    int counter_words = 0;
    while (word != NULL) {
        new_text[counter_words] = word;
        word = strtok(NULL, " .");
        counter_words++;
    }
    qsort(new_text, counter_words, sizeof(char*), qs_cmp);
    char* key = str;
    char** res = bsearch(key, new_text, counter_words, sizeof(char*), bs_cmp);

    if (res) {
        printf("exists");
    }
    else{
        printf("doesn't exist");
    }
    
    return 0;
}
