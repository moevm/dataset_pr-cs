#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_TEXT_LENGTH 1000
#define MAX_WORD_LENGTH 30
#define SENTENCE_DELIMETER " ."
#define NEW_LINE_SYMBOL '\n'
#define END_OF_STRING_SYMBOL '\0'

int compare_strings(const void *a, const void *b) {
    return strcmp(*(const char **)a, *(const char **)b);
}

void split_text(char *input_text, char **text_by_words, int *word_index) {
    char sep[10] = SENTENCE_DELIMETER;

    char *word = strtok(input_text, sep);

    while (word != NULL) {
        text_by_words[*word_index] = malloc((strlen(word) + 1) * sizeof(char));
        strcpy(text_by_words[*word_index], word);

        word = strtok(NULL, sep);
        (*word_index)++;
    }
}

void print_result(char **result) {
    if (result != NULL) {
        printf("exists");
    } else {
        printf("doesn't exist");
    }
}

int main(){

    char input_text[MAX_TEXT_LENGTH+1];
    char *text_by_words[MAX_TEXT_LENGTH+1];
    char str[MAX_WORD_LENGTH+1];
    char *strp = str;
    int word_index = 0;

    fgets(input_text, MAX_TEXT_LENGTH+1, stdin);
    fgets(str, MAX_WORD_LENGTH+1, stdin);
    input_text[strlen(input_text) - 1] = END_OF_STRING_SYMBOL;

    split_text(input_text, text_by_words, &word_index);

    qsort(text_by_words, word_index, sizeof(char *), compare_strings);

    char **result = bsearch(&strp, text_by_words, word_index, sizeof(char*), compare_strings);

    print_result(result);

}
