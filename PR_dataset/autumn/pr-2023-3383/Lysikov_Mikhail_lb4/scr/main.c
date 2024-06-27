#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_WORDS 100
#define MAX_WORD_LENGTH 100

int compareStrings(const void* a, const void* b) {
    return strcmp((const char*)a, (const char*)b);
}

int main() {
    char text[1000], tokenList[MAX_WORDS][MAX_WORD_LENGTH];
    char str[MAX_WORD_LENGTH];
    
    scanf("%999[^\n]", text);
    scanf("%29s", str);
    
    char* token = strtok(text, " ");
    int count = 0;
    
    while (token != NULL && count < MAX_WORDS) {
        strcpy(tokenList[count], token);
        count++;
        token = strtok(NULL, " ");
    }

    qsort(tokenList, count, MAX_WORD_LENGTH, compareStrings);

    char** result = (char**)bsearch(&str, tokenList, count, sizeof(tokenList[0]), compareStrings);

    if (result != NULL) {
        printf("exists\n");
    }
    else {
        printf("doesn't exist\n");
    }

    return 0;
}
