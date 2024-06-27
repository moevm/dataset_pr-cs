#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#define LEN_OF_ARR 1000

int cmp(const void *a, const void *b){
    const int *f = (const int *)a;
    const int *s = (const int *)b;
    if (*f > *s)
        return 1;
    if (*f < *s)
        return -1;
    return 0;
}

int crunching(int key, int* arr){
    for (int i = 0; i < LEN_OF_ARR; i++){
        if (arr[i] == key)
            return 1;
    }
    return 0;
}

void bsearch_time(double time_bsearch, int* key, int* arr){
    clock_t time_bsearch_start = clock();
    int* result = (int *)bsearch(key, arr, LEN_OF_ARR, sizeof(int), cmp);
    clock_t time_bsearch_end = clock();
    time_bsearch = (double)(time_bsearch_end - time_bsearch_start) / CLOCKS_PER_SEC;
    if (result)
        printf("exists\n");
    else
        printf("doesn't exist\n");
    printf("%f\n", time_bsearch);
}

void crunching_time(double time_crunching, int* key, int* arr){
    clock_t time_crunching_start = clock();
    int result = (int)crunching(*key, arr);
    clock_t time_crunching_end = clock();
    time_crunching = (double)(time_crunching_end - time_crunching_start) / CLOCKS_PER_SEC;
    if (result)
        printf("exists\n");
    else
        printf("doesn't exist\n");
    printf("%f\n", time_crunching);
}

int main(){
    double time_bsearch = 0.0; 
    double time_crunching = 0.0;
    int key = 0;
    int arr[LEN_OF_ARR];
    for (int i = 0; i < LEN_OF_ARR; i++){
        scanf("%d", (arr + i));
    }
    qsort(arr, LEN_OF_ARR, sizeof(int), cmp);

    bsearch_time(time_bsearch, &key, arr);

    crunching_time(time_crunching, &key, arr);

    return 0;
}