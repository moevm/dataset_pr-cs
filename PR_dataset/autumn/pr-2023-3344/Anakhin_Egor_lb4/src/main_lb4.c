#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int compare_bin(const void *a, const void *b) {
    return strcmp(*(const char**)a, *(const char**)b);
}

int main() {

    int len = 0;

    char text[1000];
    fgets(text, 1000, stdin);

    char* to_find = malloc(30 * sizeof(char));
    fgets(to_find, 30, stdin);

    char** sentences = malloc(1 * sizeof(char*));

    char* word = strtok(text, " .!");

    while (word != NULL) {
        sentences[len++] = word;
        sentences = realloc(sentences, (len + 1) * sizeof(char*));
        word = strtok(NULL, " .!\0");
    }

    qsort(sentences, len, sizeof(char*), compare_bin);

    char** result = (char**) bsearch(&to_find, sentences, len, sizeof(sentences[0]), compare_bin);

    if (result != NULL) {
        printf("exists");
    } else {
        printf("doesn't exist");
    }

    return 0;
}