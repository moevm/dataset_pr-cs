#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define TEXT_MAX_SIZE 100
#define NUMBER_OF_SENTENCES 10
#define END_OF_INPUT "Dragon flew away!"
#define END_OF_SENT '\0'
#define SEVEN "7"

char* space(char* str){
    char* res = calloc(strlen(str) + 1, sizeof(char));
    int start = 0;
    while (str[start] == '\t' || str[start] == ' '){
        start++;
    }
    for (int i = 0; i < strlen(str) - start; i++){
        res[i] = str[start + i];
    }
    res[strlen(str) - start] = END_OF_SENT;
    return res;
}

int hasNoSeven(char* str){
    // проврка на наличие цифры 7 в предложении
    if (strstr(str, SEVEN) == NULL){
        return 1;
    }
    return 0;
}

char** allocate_memory_for_text(){
    // выделение памяти динамическому(dynamic) массиву строк
    char **dynamic_strs = malloc(NUMBER_OF_SENTENCES * sizeof(char*));
    for(int i = 0; i < NUMBER_OF_SENTENCES; i++){
        dynamic_strs[i] = calloc(TEXT_MAX_SIZE, sizeof(char));
    } 
    return dynamic_strs;
}

char** reading_of_sentences(int* ptr_index, int* ptr_len, int* ptr_result, char** dynamic_strs){
    int overflow_str = 0;
    int overflow_mas = 0;

    char *str = calloc(TEXT_MAX_SIZE, sizeof(char));

    while (1){
        char symbol = getchar();

        str[(*ptr_index)++] = symbol;

        if ((TEXT_MAX_SIZE + overflow_str) <= (*ptr_index)){
            overflow_str++;
            str = realloc(str, (TEXT_MAX_SIZE + overflow_str) * sizeof(char));
            dynamic_strs[(*ptr_len)] = realloc(str, (TEXT_MAX_SIZE + overflow_str) * sizeof(char));
        }

        if (strstr(str, END_OF_INPUT) != NULL){
            dynamic_strs[(*ptr_len)++] = END_OF_INPUT;
            break;
        }

        if (symbol == '.' || symbol == '?' || symbol == ';'){
            str[*ptr_index] = END_OF_SENT;
            strncpy(dynamic_strs[(*ptr_len)++], str, TEXT_MAX_SIZE + overflow_str);
            overflow_str = 0;
            (*ptr_index) = 0;
            str = calloc(TEXT_MAX_SIZE, sizeof(char));
        }
        if ((NUMBER_OF_SENTENCES + overflow_mas) <= (*ptr_len)){
            overflow_mas++;
            dynamic_strs = realloc(dynamic_strs, (NUMBER_OF_SENTENCES + overflow_mas) * sizeof(char*));
            dynamic_strs[NUMBER_OF_SENTENCES + overflow_mas - 1] = calloc(TEXT_MAX_SIZE, sizeof(char));
        }
    }
    free(str);
    return dynamic_strs;
}

void output_of_sentences(int* ptr_len, int* ptr_result, char** dynamic_strs){
    for (int i = 0; i < (*ptr_len) - 1; i++){
        char* sentence = space(dynamic_strs[i]);
        if (hasNoSeven(sentence)){
            (*ptr_result)++;
            printf("%s\n", sentence);
        }
        free(sentence);
    }
    printf("%s\n", dynamic_strs[(*ptr_len) - 1]);
}

void free_memory(char** dynamic_strs, int len){
    for (int i = 0; i < len - 1; i++){
        free(dynamic_strs[i]);
    }
    free(dynamic_strs);
}

int main()
{
    char **dynamic_strs = allocate_memory_for_text();
    int index = 0;
    int* ptr_index = &index;

    int len = 0;
    int* ptr_len = &len;

    int result = 0;
    int* ptr_result = &result;

    dynamic_strs = reading_of_sentences(ptr_index, ptr_len, ptr_result, dynamic_strs);

    output_of_sentences(ptr_len, ptr_result, dynamic_strs);

    free_memory(dynamic_strs, len);

    printf("Количество предложений до %d и количество предложений после %d", len - 1, result);
    return 0;
}