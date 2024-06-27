#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int cmp(const void *a, const void *b) {
    const int *a1 = (const int *)a;
    const int *b1 = (const int *)b;
    if (*a1 > *b1) {
        return 1;
    }
    if (*a1 < *b1) {
        return -1;
    }
    return 0;
}

int main() {
    int *arr=(int *)malloc(sizeof(int)*1000);
    for (int i = 0; i < 1000; i++) {
        scanf("%d", &arr[i]);
    }
    qsort(arr, 1000, sizeof(int), cmp);
    int null=0;
    clock_t startTime = clock();
    int *res = (int *)bsearch(&null, arr, 1000, sizeof(int), cmp);
    clock_t endTime = clock();
    double timeSpent = (double)(endTime - startTime) / CLOCKS_PER_SEC;
    if (res) {
        printf("%s\n", "exists");
    }
    else {
    printf("%s\n", "doesn't exist");
    }
    printf("%f\n", timeSpent);

    int prov = 0;
    startTime = clock();
    for (int j = 0; j < 1000; j++) {
        if (arr[j] == 0) {
            prov = 1;
        }
    }
    endTime = clock();
    double timeSpent2raz = (double)(endTime - startTime) / CLOCKS_PER_SEC;
    if (prov == 1) {
        printf("%s\n", "exists");
    }
    else {
        printf("%s\n", "doesn't exist");
    }
    printf("%f\n", timeSpent2raz);
    free(arr);
    return 0;
}
