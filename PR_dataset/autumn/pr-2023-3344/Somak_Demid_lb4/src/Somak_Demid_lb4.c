#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int cmp(const void *a, const void *b) {
    return strcmp(*(const char**)a, *(const char**)b);
}

int main() {

    char string[1001];
    fgets(string, 1001, stdin);
    if (string[strlen(string)-1] == '\n'){
        string[strlen(string)-1] = '\0';
    }

    char* key = malloc(31 * sizeof(char));
    fgets(key, 31, stdin);
    if (key[strlen(key)-1] == '\n'){
        key[strlen(key)-1] = '\0';
    }

    unsigned capacity = 10;
    unsigned i = 1;
    char** arrofwords = malloc(capacity*sizeof(char*));

    char* word = strtok(string, " .");
    unsigned wordcount = 0;
    while (word != NULL) {
        arrofwords[wordcount] = word;
        if(wordcount == capacity){
            i++;
            capacity *= i;
            arrofwords = realloc(arrofwords, sizeof(char*) * capacity);
        }
        wordcount++;
        word = strtok(NULL, " .");
    }

    qsort(arrofwords, wordcount, sizeof(char*), cmp);
    char** res = bsearch(&key, arrofwords, wordcount, sizeof(char*), cmp);

    free(key);
    free(arrofwords);

    (res == NULL) ? printf("doesn't exist") : printf("exists");

    return 0;
}
