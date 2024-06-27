#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TEXT_LEN 1000
#define STR_LEN 30

int sort_words(const void *word_1, const void *word_2) {
    const char **word1 = (const char **)word_1;
    const char **word2 = (const char **)word_2;
    return strcmp(*word1, *word2);
}

int compare_exist(const void *word_1, const void *word_2) {
    const char *word1 = (const char *)word_1;
    const char **word2 = (const char **)word_2;
    return strcmp(word1, *word2);
}

int main()
{
    char text[TEXT_LEN];
    fgets(text, TEXT_LEN, stdin);

    char str[STR_LEN];
    fgets(str, STR_LEN, stdin);
    if(str[strlen(str) - 1] == '\n') {
        str[strlen(str) - 1] = '\0';
    }

    char **text_to_words = malloc(sizeof(char *));
    char *word = strtok(text, " .");
    int count = 0;
    while (word != NULL) {
        if(str[strlen(word) - 1] == '\n') {
            str[strlen(word) - 1] = '\0';
        }
        text_to_words[count] = word;
        count++;
        word = strtok(NULL, " .");
        text_to_words = realloc(text_to_words, (count + 1) * sizeof(char *));
    }
    text_to_words = realloc(text_to_words, count * sizeof(char *));
    qsort(text_to_words, count, sizeof(char *), sort_words);

    char **result = bsearch(&str, text_to_words, count, sizeof(char *), compare_exist);
    if (result) {
        printf("exists");
    }
    else {
        printf("doesn't exist");
    }

    free(text_to_words);
    return 0;
}