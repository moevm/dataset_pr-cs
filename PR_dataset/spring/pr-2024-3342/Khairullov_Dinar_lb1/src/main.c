#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>


#define END_OF_THE_TEXT "Fin."
#define MEMORY_ERROR "Error: error reallocating memory\n"
#define COMPILE_REGEX_ERROR "Cant't compile regular expression\n"
#define MEMORY_ALLOCATING_ERROR_PRINT "Error: memory allocating error\n"
#define MEMORY_ALLOCATING_ERROR_EXIT 40

char** text_input(int* num_of_sentences);
void clean_memory(char** text, int* num_of_sen);


char** text_input(int* num_of_sentences){
    int current_symbol_index = 0;
    int current_sentence_index = 0;
    char symbol;
    char** text = (char**)malloc(1*sizeof(char*));
    if(text == NULL)
    {
        printf(MEMORY_ALLOCATING_ERROR_PRINT);
        exit(MEMORY_ALLOCATING_ERROR_EXIT);
    }
    
    text[current_sentence_index] = (char*)malloc(1*sizeof(char));
    if(text[current_sentence_index] == NULL)
    {
        printf(MEMORY_ALLOCATING_ERROR_PRINT);
        exit(MEMORY_ALLOCATING_ERROR_EXIT);
    }

    while(strstr(text[current_sentence_index], END_OF_THE_TEXT) == NULL){
        symbol = getchar();
        if(symbol == '\n'){
            text[current_sentence_index][current_symbol_index] = '\0';
            current_symbol_index = 0;
            current_sentence_index++;
            
            text = (char**)realloc(text, (current_sentence_index + 1)*sizeof(char*));
            if(text == NULL)
            {
                printf(MEMORY_ALLOCATING_ERROR_PRINT);
                exit(MEMORY_ALLOCATING_ERROR_EXIT);
            }
            
            text[current_sentence_index] = (char*)malloc(1*sizeof(char));
            if(text[current_sentence_index] == NULL)
            {
                printf(MEMORY_ALLOCATING_ERROR_PRINT);
                exit(MEMORY_ALLOCATING_ERROR_EXIT);
            }
        }
        else{
            text[current_sentence_index][current_symbol_index] = symbol;
            current_symbol_index++;
            text[current_sentence_index] = (char*)realloc(text[current_sentence_index], (current_symbol_index + 1)*sizeof(char));
            if(text[current_sentence_index] == NULL)
            {
                printf(MEMORY_ALLOCATING_ERROR_PRINT);
                exit(MEMORY_ALLOCATING_ERROR_EXIT);
            }
        }
    }
    text[current_sentence_index][current_symbol_index] = '\0';
    *num_of_sentences = current_sentence_index;

    return text;
}



void clean_memory(char** text, int* num_of_sen){
    for(int i = 0; i <= *num_of_sen; i++){
        free(text[i]);
    }
    free(text);
}


int main(){
    char** text;
    int num_of_sentences = 0;
    text = text_input(&num_of_sentences);

    char* regexString = "(:\\/\\/)?(www\\.)?(([A-z0-9]+\\.)+[A-z0-9]+)\\/([A-z0-9]+\\/)*([A-z0-9]+\\.[A-z0-9]+)\0";
    size_t maxGroups = 7;
    regex_t regexCompiled;
    regmatch_t groupArray[maxGroups];
    if(regcomp(&regexCompiled, regexString, REG_EXTENDED)){
        printf(COMPILE_REGEX_ERROR);
        return 0;
    }

    for(int i = 0; i <= num_of_sentences; i++){
        if(regexec(&regexCompiled, text[i], maxGroups, groupArray, 0) == 0){
            if(groupArray[3].rm_so == -1 || groupArray[6].rm_so == -1){
                break;
            }
            for(int y = groupArray[3].rm_so; y < groupArray[3].rm_eo; y++){
                printf("%c", text[i][y]);
            }
            printf(" - ");
            for(int y = groupArray[6].rm_so; y < groupArray[6].rm_eo; y++){
                printf("%c", text[i][y]);
            }
            printf("%c", '\n');
        }

    }

    clean_memory(text, &num_of_sentences);
    regfree(&regexCompiled);

    return 0;

}