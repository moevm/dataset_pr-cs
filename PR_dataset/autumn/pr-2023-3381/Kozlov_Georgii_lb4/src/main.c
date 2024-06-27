#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define NUM 1000

int cmp_srt(const void *a, const void *b);

int secsrt(int* arr, int key) {
for (int k = 0; k < NUM; k++) {
    if (arr[k]==key) return 1;
    return 0;
    }
}
int main() {
    int *arr1 = malloc(sizeof(int) * NUM);
    int *arr2 = malloc(sizeof(int) * NUM);
    int x;
    int key = 0;
    clock_t start_t, end_t;
    for (int j = 0; j < NUM; j++){
    scanf("%d", &x);
    arr1[j] = x;
    arr2[j] = x;
    }   
    start_t = clock();
    qsort(arr1, NUM, sizeof(int), &cmp_srt);
    int *test = bsearch(&key, arr1, NUM, sizeof(int), &cmp_srt);
    end_t = clock();
    double ftotal_t = (double)(end_t - start_t)/CLOCKS_PER_SEC;
    if (test != NULL) puts("exists");
    else puts("doesn't exist");
    printf("%lf\n", ftotal_t);
    start_t = clock();
    int sec_res = secsrt(arr2, key);
    end_t = clock();
    double stotal_t = (double)(end_t - start_t)/CLOCKS_PER_SEC;
    if (sec_res == 1) puts("exists");
    else puts("doesn't exist");
    printf("%lf\n", stotal_t);
    free(arr1);
    free(arr2);
}

int cmp_srt(const void *a, const void *b) {
    int f = *(const int *)(a);
    int s = *(const int *)(b);
    if (f > s) return 1;
    if (f < s) return -1;
    return 0;
}
