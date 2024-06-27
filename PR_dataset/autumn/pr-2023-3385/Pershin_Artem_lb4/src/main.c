#include <stdio.h>
#include <stdlib.h>
#include <time.h>


int cmp(const void *a, const void *b){
    int* f = (int*)a;
    int* s = (int*)b;
    if(*f > *s){
        return 1;
    }
    if(*f < *s){
        return -1;
    }
    return 0;
}


int main() {
    int arr[1000];
    for (int i = 0; i < 1000; i++){
        scanf("%d", &arr[i]);
    }
    int zero = 0;
    clock_t start_time, end_time;
    double search_time;
    qsort(arr, 1000, sizeof(int), cmp);
    start_time = clock();
    int* findzero = bsearch(&zero, arr, 1000, sizeof(int), cmp);
    end_time = clock();
    search_time = ((double) (end_time - start_time)) / CLOCKS_PER_SEC;
    if(findzero){
        printf("exists\n");
    }
    else{
        printf("doesn't exist\n");
    }
    printf("%f\n", search_time);
    start_time = clock();
    int ifzerofound = 0;
    for (int i = 0; i < 1000; i++) {
        if (arr[i] == 0) {
            ifzerofound = 1;
            break;
        }
    }
    end_time = clock();
    search_time = ((double) (end_time - start_time)) / CLOCKS_PER_SEC;
    if(ifzerofound){
        printf("exists\n");
    }
    else{
        printf("doesn't exist\n");
    }
    printf("%f\n", search_time);
    return 0;
}