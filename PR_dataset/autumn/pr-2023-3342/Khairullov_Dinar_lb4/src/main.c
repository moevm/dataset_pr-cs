#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define TEXT_MAX_SIZE 1000
#define WORD_MAX_SIZE 30



void input(char* text, char* check_word){
    int sym_index = 0;
    char sym = getchar();
    
    while(sym != '\n'){
        text[sym_index] = sym;
        sym_index++;
        sym = getchar();
    }
    
    fgets(check_word, WORD_MAX_SIZE, stdin);
}



char** separator(char* text, int* words_counter){
    char** sep_text = malloc(sizeof(char*));
    char* word = strtok(text, " .");
    while(word != NULL){
        sep_text[*words_counter] = malloc((strlen(word))*sizeof(char));
        strcpy(sep_text[*words_counter], word);
        (*words_counter)++;
        word = strtok(NULL, " .");
        sep_text = realloc(sep_text, ((*words_counter)+1)*sizeof(char*));
    }
    return sep_text;
}



int qsort_str_cmp(const void* first_str, const void* second_str){
    const char* str_first = *(const char**)first_str;
    const char* str_second = *(const char**)second_str;
    return(strcmp(str_first, str_second));
}

int bsearch_str_cmp(const void* key, const void* val){
    const char* word = (const char*)key;
    const char** sep_text = (const char**)val;
    return strcmp(word, *sep_text);
}


void output(char** flag){
    if(flag != NULL){
        printf("exists\n\n");
    }
    else{
        printf("doesn't exist\n\n");
    }
}



int main(){
    int words_number = 0;
    char text[TEXT_MAX_SIZE];
    char check_word[WORD_MAX_SIZE];
    
    input(text, check_word);
    
    char** sep_text = separator(text, &words_number);
    
    qsort(sep_text, words_number, sizeof(char*), qsort_str_cmp);
    char** flag = bsearch(check_word, sep_text, words_number, sizeof(char*), bsearch_str_cmp);
    
    output(flag);
    
    
    return 0;
}