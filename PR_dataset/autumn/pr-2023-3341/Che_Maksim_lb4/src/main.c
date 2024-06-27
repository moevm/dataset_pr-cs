#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int compare(const void* a, const void* b) {
    return strcmp(*(char**)a, *(char**)b);
}
int compare_search(const void* a, const void* b) {
    return strcmp((char*)a, *(char**)b);
}

int main() {
    char text[1000] = {0};
    char str[30] = {0};
    char* words[1000] = {0};
    int count = 0;

    fgets(text, sizeof(text), stdin);

    scanf("%s", str);

    char* word = strtok(text, " .");
    while (word != NULL) {
        words[count++] = word;
        word = strtok(NULL, " .");
    }

    qsort(words, count, sizeof(char*), compare);

    if (bsearch(&str, words, count, sizeof(char**), compare_search)) {
        printf("exists\n");
    } else {
        printf("doesn't exist\n");
    }
    return 0;
}
