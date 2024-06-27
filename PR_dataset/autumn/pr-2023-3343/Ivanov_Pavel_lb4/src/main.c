#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int cmp_key(const void* first_, const void* second_){
    const char* first = (const char*)first_;
    const char* second = *((const char**)second_);
    return strcmp(first, second);
}

int cmp_words(const void* first_, const void* second_){
    const char* first = *((const char**)first_);
    const char* second = *((const char**)second_);
    int result = strcmp(first, second);
    if(result > 0){
        return 1;
    }
    if(result < 0){
        return -1;
    }
    return 0;
}

int main(){
    char text[1000];
    char substr[30];
    char* word;
    char** words = malloc(sizeof(char*));
    int ct = 0;

    fgets(text, 1000, stdin);
    fgets(substr, 30, stdin);

    if(substr[strlen(substr) - 1] == '\n'){
        substr[strlen(substr) - 1] = '\0';
    }
    word = strtok(text, " .");
    while(word != NULL){
        if(word[strlen(word) - 1] == '\n'){
            word[strlen(word) - 1] = '\0';
        }
        words[ct++] = word;
        word = strtok(NULL, " .");
        words = realloc(words, (ct + 1) * sizeof(char*));
    }

    qsort(words, ct, sizeof(char*), cmp_words);
    char** result = (char**)bsearch(&substr, words, ct, sizeof(char*), cmp_key);

    if(result){
        printf("exists");
    }else{
        printf("doesn't exist");
    }
    
    free(words);
}
