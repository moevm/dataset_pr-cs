#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define TEXT_SIZE 1000
#define STR_SIZE 30

int cmp_qsort(const void* first, const void* second){
    const char **first_word = (const char **)first;
    const char **second_word = (const char **)second;
    return strcmp(*first_word, *second_word);
}

int cmp_bsearch(const void *key, const void *value){
    const char* str = (const char*)key;
    const char** words = (const char**)value;
    return strcmp(str, *words);
}

char* read_text(){
    int capacity_of_text = TEXT_SIZE;
    int idx = 0;
    char symbol = getchar();
    char* text = (char*)malloc(capacity_of_text);
    while(1){
        if(symbol == '\n'){
        break;
        }
        if(symbol == '\"'){
            symbol = getchar();
            continue;
        }
        text[idx++] = symbol;
        symbol = getchar();
    }
    return text;
}

char* read_str(){
    int capacity_of_str =  STR_SIZE;
    char* str = (char*)malloc(sizeof(char) * capacity_of_str);
    fgets(str,(STR_SIZE+1),stdin);
    str[strlen(str)] = '\0';
    return str;
}

char** get_words(char* text, int* length){
    char* word;
    char sep[] = " .";
    char** words = (char**)malloc(TEXT_SIZE*sizeof(char*));
    word = strtok(text,sep);
    while (word != NULL){
        words[*length] = word;
        (*length)++;
        word = strtok (NULL,sep);
    }
    return words;
}

void answer(char** result){
    if(result){
        printf("exists");
    }
    else{
        printf("doesn't exist");
    }
    
}

void clean_memory(char* text, char* str, char** words){
    free(words);
    free(text);
    free(str);
}



int main(){
    char* text = read_text();
    char* str = read_str();
    int length = 0;
    char** words = get_words(text, &length);
    qsort(words, length, sizeof(char*), cmp_qsort);
    char** result = bsearch(str, words, length, sizeof(char*), cmp_bsearch);
    answer(result);
    clean_memory(text, str, words);

    return 0;
}