#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int compare(const void * a, const void * b) {
   return strcmp(*(const char **)a, *(const char **)b);
}

int bnsearch(const void* a, const void* b) {
    const char* f = (const char*) a;
    const char** s = (const char**) b;
    return strcmp(f, *s);
}

int main() {
    char text[5000];
    char str[30];
    int i = 0;

    fgets(text, sizeof(text), stdin);
    scanf("%s", str);
    
    int count = 0;
    
    for (i; i < strlen(text); i++) {
        if ((text[i] == ' ' || text[i] == '.') && text[i+1] != ' ') {
            count++;
        }
    }
    
    char *words[count];
    char *token;
    char *saveptr;
    
    token = strtok_r(text, " .", &saveptr);
    
    int index = 0;
    while (token != NULL) {
        words[index++] = token;
        token = strtok_r(NULL, " .", &saveptr);
    }
    
    qsort(words, count, sizeof(char*), compare);

    char** result = (char**)bsearch(&str, words, count, sizeof(words[0]), bnsearch);
    
    if (result != NULL) {
        puts("exists");
    } else {
        puts("doesn't exist");
    }
    
    return 0;
}
