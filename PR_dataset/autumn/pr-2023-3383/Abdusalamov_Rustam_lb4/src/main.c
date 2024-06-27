#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define TEXT_LENGTH 10000
#define WORD_LENGTH 150

int cmpStr(const void *a, const void *b)
{
    return strcmp(*(const char **)a, *(const char **)b);
}

int main() {
    char* text = malloc(TEXT_LENGTH);
    char* word = malloc(WORD_LENGTH);
    fgets(text,TEXT_LENGTH,stdin);
    fgets(word,WORD_LENGTH,stdin);
    char** words = (char**)malloc(WORD_LENGTH*sizeof(char*));
    char* token = strtok(text, " .");
    int count = 0;
    while (token != NULL){
        words[count++] = token;
        token = strtok(NULL," .");}
    qsort(words, count, sizeof(char**), cmpStr);
    if(bsearch(&word, words, count, sizeof(char**),cmpStr))
        printf("exists");
    else
        printf("doesn't exist");
    free(word);
    free(text);
    return 0;
}
