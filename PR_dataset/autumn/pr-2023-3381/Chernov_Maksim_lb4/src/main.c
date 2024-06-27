#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int compare(const void *a, const void *b) {
    return strcmp(*(const char **)a, *(const char **)b);
}
int binarySearch(char **words, int start, int end, const char *str) {
    if (start <= end) {
        int mid = (start + end) / 2;
        int cmp = strcmp(words[mid], str);
        if (cmp == 0) {
            return 1;
        } else if (cmp < 0) {
            return binarySearch(words, mid + 1, end, str);
        } else {
            return binarySearch(words, start, mid - 1, str);
        }
    }
    return 0;
}
int main() {
    char text[1001];
    char str[31];
    scanf("%[^\n]%*c", text);
    scanf("%s", str);
    char *words[1000];
    int wordCount = 0;
    char *word = strtok(text, " .");
    while (word != NULL) {
        words[wordCount] = word;
        wordCount++;
        word = strtok(NULL, " .");
    }
    qsort(words, wordCount, sizeof(char *), compare);
    int exists = binarySearch(words, 0, wordCount - 1, str);
    if (exists) {
        printf("exists");
    } else {
        printf("doesn't exist");
    }
    return 0;
}