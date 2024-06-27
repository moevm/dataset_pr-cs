#include <stdio.h>  
#include <stdlib.h>
#include <string.h> 
#define NULL_TERMINATOR '\0'
#define TEXT_SIZE 1001
#define WORD_SIZE 31
int cmp_qsort(const void *a, const void *b){
    const char **f = (const char **)a;
    const char **s = (const char **)b;
    return strcmp(*f, *s);
}
int cmp_bsearch(const void *key, const void *val){
    const char* k = (const char*) key;
    const char **v = (const char **) val;
    return strcmp(k, *v);
}
int data_input(char* text_input, char* word_to_search, char** words_separated){
    fgets(text_input, TEXT_SIZE, stdin);
    fgets(word_to_search, WORD_SIZE, stdin);
    word_to_search = strtok (word_to_search," .,;!()''");
    char* word = strtok (text_input," .,;!'?'");
    int last_word_index = 0;
    while (word!=NULL){
        if (word[strlen(word)-1] == '\n'){
            word[strlen(word)-1] = NULL_TERMINATOR;
        }
        words_separated[last_word_index] = word;
        last_word_index++;
        word = strtok (NULL," !.,;()''");
    }
    return last_word_index;
}
void data_output(char* word_to_search, char** words_separated, int last_word_index){
    qsort(words_separated, last_word_index, sizeof(char*), cmp_qsort);
    char** search_check = bsearch(word_to_search, words_separated, last_word_index, sizeof(char*), cmp_bsearch);
    if (search_check!=NULL){
        printf("exists");
    }else{
        printf("doesn't exist");
    }
}
int main(){
    char* text_input = (char*)malloc(TEXT_SIZE);
    char* word_to_search = (char*)malloc(WORD_SIZE);
    char **words_separated = malloc(TEXT_SIZE*sizeof(char*));
    int last_word_index = data_input(text_input, word_to_search, words_separated);
    data_output(word_to_search, words_separated, last_word_index);
    return 0;
}
