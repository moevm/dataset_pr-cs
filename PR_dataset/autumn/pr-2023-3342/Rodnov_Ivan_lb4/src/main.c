#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_TEXT_SIZE 1000
#define MAX_WORD_SIZE 30
#define NEW_LINE '\n'

char* input_text(){
    char* text = malloc(MAX_TEXT_SIZE * sizeof(char));
    fgets(text, MAX_TEXT_SIZE, stdin);
    text[strlen(text) - 1] = NEW_LINE;
    return text;
}

char** split_text(char* text, int* count_words){
    char** splited_text = malloc(MAX_TEXT_SIZE * sizeof(char*));
    char* word;
    int i = 0;

    word = strtok(text, " .");
    while(word != NULL){
        splited_text[i] = malloc(MAX_WORD_SIZE * sizeof(char));
        strcpy(splited_text[i], word);
        word = strtok(NULL, " .");
        i++;
    }
    *count_words = i;

    return splited_text;
}

int cmp(const void *a, const void *b){
    return strcmp(*(const char **)a, *(const char **)b);
}

void answer(char **ans) {
    if (ans != NULL) {
        printf("exists");
    } 
    else {
        printf("doesn't exist");
    }
}

int main()
{
    char* input = input_text();
    int count_words;
    char** splited_text = split_text(input, &count_words);
    char key_word[MAX_WORD_SIZE];

    fgets(key_word, MAX_WORD_SIZE, stdin);

    qsort(splited_text, count_words, sizeof(char*), cmp);

    char* key = key_word;
    char** ans = (bsearch(&key, splited_text, count_words, sizeof(char *), cmp));

    answer(ans);

    for (int i = 0; i < count_words; i++) {
        free(splited_text[i]);
    }
    free(input);
    free(splited_text);
    return 0;
}
