#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define TEXT_SIZE 1000
#define WORD_SIZE 30
#define MAX_WORDS 1000

int compare(const void *a, const void *b) {
    return strcmp(*(const char **)a, *(const char **)b);
}

int binarySearch(char** words, int size, char* str, int left, int right) {
    while (left <= right) {
        int index_middle_array = left + (right - left) / 2;

        if (strcmp(words[index_middle_array], str) == 0) {
            return 1;
        } else if (strcmp(words[index_middle_array], str) < 0) {
            left = index_middle_array + 1;
        } else {
            right = index_middle_array - 1;
        }
    }

    return 0;
}

int tokenizeAndSort(char *text, char *words[], int *numWords) {
    char *word;
    *numWords = 0;

    word = strtok(text, " .\n");
    while (word != NULL) {
        words[*numWords] = strdup(word);
        (*numWords)++;
        word = strtok(NULL, " .\n");
    }

    qsort(words, *numWords, sizeof(char*), compare);
}

int main() {
    char text[TEXT_SIZE];
    char str[WORD_SIZE];
    fgets(text, sizeof(text), stdin);
    scanf("%s", str);

    char* words[MAX_WORDS];
    int wordCount;

    tokenizeAndSort(text, words, &wordCount);

    if (binarySearch(words, wordCount, str, 0, wordCount - 1)) {
        printf("exists\n");
    } else {
        printf("doesn't exist\n");
    }

    for (int i = 0; i < wordCount; i++) {
        free(words[i]);
    }

    return 0;
}


