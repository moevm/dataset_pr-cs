#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int cmp(const void *a, const void *b) {
    const char **f1 = (const char **)a;
    const char **f2 = (const char **)b;
    return strcmp(*f1, *f2);
}

int cmp2(const void *key, const void *val) {
    const char *f1 = (const char *)key;
    const char **f2 = (const char **)val;
    return strcmp(f1, *f2);
}

int main() {
    int n = 1000, count1 = 0, count2 = 0;
    char text[n], str[30];
    fgets(text, n, stdin);
    fgets(str, 30, stdin);
    char **arr = malloc(sizeof(int*) * n);
    for (int i = 0; i < n; i++) {
        arr[i] = malloc(sizeof(char) * n);
    }
    for (int i = 0; text[i]; i++) {
        if (text[i] == '\n') {
            text[i] = '\0';
        }
        if (text[i] == ' ' || text[i] == '.') {
            if (text[i - 1] == ' ' || text[i - 1] == '.') {
                continue;
            } else {
                arr[count1][count2] = '\0';
                count1++;
                count2 = 0;
                continue;
            }
        }
        arr[count1][count2] = text[i];
        count2++;
    }
    for (int i = 0; str[i]; i++) {
        if (str[i] == '\n') {
            str[i] = '\0';
        }
    }
    qsort(arr, count1, sizeof(char*), cmp);
    char **res = bsearch(str, arr, count1, sizeof(char*), cmp2);
    if (res) {
        printf("exists");
    } else {
        printf("doesn't exist");
    }
    for (int i = 0; i < n; i++) {
        free(arr[i]);
    }
    free(arr);
    return 0;
}