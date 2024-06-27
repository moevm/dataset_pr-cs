#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MEMORY_CHUNK 20;
#define SPLITTERS "."

char* get_text_input(char* str);
char** split_text(char *text, unsigned int *num_words);
int compare_strings (const void *a, const void *b);
int cmpkey (const void *a, const void *b);

int main(void) {

    unsigned int num_words = 0;
    char str[30];

    char* text = get_text_input(str);
    char** splitted_text = split_text(text, &num_words);

    qsort (splitted_text, num_words, sizeof(char*), compare_strings);
    char** res = (char**)bsearch(&str, splitted_text, num_words, sizeof(char*), cmpkey);

    if(res)
        printf("exists");
    else
        printf("doesn't exist");

    free(text);
    return 0;
}


char* get_text_input(char* str) {
    unsigned int size = 0, capacity = MEMORY_CHUNK;
    char ch;
    char* text = (char*)malloc(capacity*sizeof(char));
    while ((ch = getchar()) != '\n') {

        if (size >= capacity - 1){
            capacity += MEMORY_CHUNK;
            text = realloc(text, capacity * sizeof(char));
        }
        text[size++] = ch;

    }
    text[size] = '\0';
    scanf("%s", str);
    return text;
}

char** split_text(char * text, unsigned int * num_words){

    char * pch = strtok (text," ");
    char** splitted_text = (char**)malloc(sizeof(char*));
    unsigned int word_count = 0;
    while (pch != NULL)
    {
        splitted_text = (char**)realloc(splitted_text, sizeof(char*) * (word_count + 1));
        splitted_text[word_count++] = (char*)malloc(sizeof(char)*(strlen(pch)-1));
        splitted_text[word_count - 1] = strdup(pch);
        pch = strtok (NULL, " ");
    }

    *num_words = word_count;
    return splitted_text;
}
int compare_strings (const void *a, const void *b) {
    return strcmp(*(char **)a, *(char **)b);
}
int cmpkey (const void *a, const void *b) {
    return strcmp((char *)a, *(char **)b);
}
