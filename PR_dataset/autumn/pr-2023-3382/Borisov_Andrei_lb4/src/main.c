#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define LEN 1000
int cmp(const void* a, const void *b) {
    const int *first = (const int *) a, *second = (const int *)b;
    if (*first > *second) 
        return 1;
    if (*first < *second) 
        return -1;
    return 0;
}
int linear_search(const int arr[], int len, int key) {
    for (int i = 0; i < len; i++) {
        if (arr[i] == key) {
            return 1;
        }
    }
    return 0;
}
int main() {
    int arr[LEN];
    for (int i = 0; i < LEN; i++)
        scanf("%d", &arr[i]);
    qsort(arr, LEN, sizeof(int), cmp);
    clock_t start = clock();
    int key = 0;
    int *bin_search_res = (int*)bsearch(&key, arr, LEN, sizeof(int), cmp);
    clock_t end = clock();
    double bin_search_time = (double) (end - start) / CLOCKS_PER_SEC;
    puts(bin_search_res ? "exists" : "doesn't exist");
    printf("%f\n", bin_search_time);
    start = clock();
    int linear_search_res = linear_search(arr, LEN, 0);
    end = clock();
    double linear_search_time = (double) (end - start) /
    CLOCKS_PER_SEC;
    puts(linear_search_res ? "exists\n" : "doesn't exist\n");
    printf("%f\n", linear_search_time);
    return 0;
}