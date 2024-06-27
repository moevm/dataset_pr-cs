#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define TEXT_SIZE 1000
#define WORD_SIZE 30
#define MAX_NUMBER_OF_WORDS 500

char **get_array_of_words(int *lenght);
int compare_str(const void *a, const void *b);
void result_output(char **res);

int main(void){
    int length = 0;
    char search_word[WORD_SIZE];
    char **array_of_words = get_array_of_words(&length);
    fgets(search_word, WORD_SIZE, stdin);
    char *pointer = search_word;
    qsort(array_of_words, length, sizeof(char*), compare_str);
    char **res = bsearch(&pointer, array_of_words, length, sizeof(char*), compare_str);
    result_output(res);
    return 0;
}   

char **get_array_of_words(int *length){
    char input_string[TEXT_SIZE];
    fgets(input_string, TEXT_SIZE, stdin);
    input_string[strlen(input_string) - 1] = '\n';

    char **words = malloc(MAX_NUMBER_OF_WORDS * sizeof(char*));
    char *word = strtok(input_string, " .");

    while (word != NULL){
        words[*length] = malloc(strlen(word) * sizeof(char));
        strcpy(words[*length], word);
        (*length)++;
        word = strtok(NULL, " .");
    }

    return words;
}

int compare_str(const void *a, const void *b){
    return strcmp(*(const char **)a, *(const char **)b);
}

void result_output(char **res){
    if (res != NULL){
        printf("exists");
        return;
    }
    printf("doesn't exist");

}