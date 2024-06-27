#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MULT_SIZE 2


int compare_bin(const void* a, const void* b) {
    return strcmp(*(const char**)a, *(const char**)b);
}

int main() {
    int top = 0;
    char* line = (char*)malloc(sizeof(char));
    char c;
    int capacity = 1;
    while((c = getchar()) != '\n'){
        line[top++] = c;
        if(top >= capacity){
            capacity *= MULT_SIZE;
            line = (char*)realloc(line, (sizeof(char) * capacity));
        }
    } line[top] = '\0';

    top = 0;
    char* str_for_srch = malloc(sizeof(char) * 30);
    fgets(str_for_srch, 30, stdin);
    char** words = (char**)malloc(sizeof(char*));
    char* token = strtok(line, " .");
    while(token != NULL){
        words[top++] = token;
        words = (char**)realloc(words, sizeof(char*) * (top + 1));
        token = strtok(NULL, " ");
    }
    qsort(words, top, sizeof(char*), compare_bin);
    char** result = (char**)bsearch(&str_for_srch, words, top, sizeof(words[0]), compare_bin);

    if (result != NULL) {
        printf("exists");
    } else {
        printf("doesn't exist");
    }
    return 0;
}
