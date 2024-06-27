#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>


int compare(const void* a, const void* b) {
    return strcmp(*(const char**)a, *(const char**)b);
}
bool bs(char* word, char** words, int size) {
    int left = 0;
    int right = size - 1;

    while (left <= right) {
        int middle = (left + right) / 2;
        int cr = strcmp(word, words[middle]);

        if (cr == 0) {
            return true;
        } else if (cr < 0) {
            right = middle - 1;
        } else {
            left = middle + 1;
        }
    }
    return false;
}
int main() {
    char text[1000];
    char word[31];
    char* words[1000];
    int size = 0;
    fgets(text, sizeof(text), stdin);
    fgets(word, sizeof(word), stdin);
    char* token = strtok(text, " .\n");
    while (token != NULL) {
        words[size] = strdup(token);
        size++;
        token = strtok(NULL, " .\n");
    }
    qsort(words, size, sizeof(char*), compare);
    bool exists = bs(word, words, size);
    if (exists) {
        printf("exists\n");
    } else {
        printf("doesn't exist\n");
    }
    return 0;
}
