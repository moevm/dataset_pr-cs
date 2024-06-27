#include <stdlib.h>
#include <string.h>
#include <stdio.h>

int compare(const void *a, const void *b)
{
    return strcmp(*(const char **)a, *(const char **)b);
}

int binary_search(char *arr[], int left, int right, char *str)
{
    while (left <= right) {
        int mid = left + (right - left) / 2;
        int result = strcmp(arr[mid], str);

        if (result == 0) {
            return 1;
        } else if (result < 0) {
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }
    return 0; // not found
}

int main(){

    char arr[1001];
    char str[31];

    fgets(arr,sizeof(arr), stdin);
    arr[strcspn(arr,"\n")] = '\0';

    fgets(str,sizeof(str), stdin);
    str[strcspn(str,"\n")] = '\0';

    char *words[1000];
    int wordCount = 0;

    char *token = strtok(arr, " .");
    while (token != NULL) {
        words[wordCount++] = token;
        token = strtok(NULL, " .");
    }

    qsort(words, wordCount, sizeof(char *), compare);

    int result = binary_search(words, 0, wordCount - 1, str);

    if (result) {
        printf("exists\n");
    } else {
        printf("doesn't exist\n");
    }

    return 0;
}