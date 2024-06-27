#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define TEXT_SIZE 1000
#define STR_SIZE 30

int compare(const void *a, const void *b) {

    return strcmp(*(const char **)a, *(const char **)b);

}

int binary_search(char **words, int words_counter, char *str) {

    int left = 0;
    int right = words_counter - 1;
    
    while (left <= right) {

        int middle = left + (right - left) / 2;
        int cmp = strcmp(words[middle], str);

        if (cmp == 0){ 
            return 1;
        }else if (cmp < 0){
            left = middle + 1;
        }else{
            right = middle - 1;
        }
    }   
    
    return 0;

}

void split_text(char *text, char **words, int *words_counter) {

    char *word = strtok(text, " .");

    while (word != NULL) {
        words[*words_counter] = strdup(word);
        word = strtok(NULL, " .");
        (*words_counter)++;
    }

}   

void result(char **words, int words_counter, char *str) {

    qsort(words, words_counter, sizeof(char *), compare);

    if (binary_search(words, words_counter, str)) {
        printf("exists");
    } else { 
        printf("doesn't exist");
    }

}

int main() {

    char text[TEXT_SIZE];
    char str[STR_SIZE];

    fgets(text, sizeof(text), stdin);
    scanf("%s", str);

    char **words = malloc(TEXT_SIZE * sizeof(char *));
    int words_counter = 0;

    split_text(text, words, &words_counter);
    result(words, words_counter, str);

    return 0;

}
