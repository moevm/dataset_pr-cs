#include <stdio.h>
#include <time.h>
#include <stdlib.h>

int cmp(const void *a, const void *b){
    const int *f = (const int *)a;
    const int *s = (const int *)b;
    if (*f > *s){
        return 1;
    } else if (*f < *s){
        return -1;
    } else {
        return 0;
    }
}

int main(){
    int arr[1000];
    clock_t start_bsearch, stop_bsearch;
    clock_t start_search, stop_search;
    double time_bsearch, time_search;
    for (int i = 0; i < 1000; i++){
        scanf("%d", &arr[i]);
    }
    qsort(arr, 1000, sizeof(int), cmp);
    
    int key = 0;
    start_bsearch = clock();
    int *result = bsearch(&key, arr, 1000, sizeof(int), cmp);
    stop_bsearch = clock();
    if (result != NULL){
        printf("exists\n");
    } else {
        printf("doesn't exist\n");
    }
    time_bsearch = stop_bsearch - start_bsearch;
    printf("%f\n", time_bsearch);
    
    int flag = 0;
    start_search = clock();
    for (int j = 0; j < 1000; j++){
        if (arr[j] == 0){
            flag = 1;
            break;
        }
    }
    stop_search = clock();
    if (flag == 1){
        printf("exists\n");
    } else {
        printf("doesn't exist\n");
    }
    time_search = stop_search - start_search;
    printf("%f\n", time_search);
    return 0;
}
