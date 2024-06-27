#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int cmp(const void* a, const void* b){
    int f = abs(*(const int*) a);
    int s = abs(*(const int*) b);
    if(f > s)
        return -1;
    if(f < s)
        return 1;
    return 0;
}

int main(){
    clock_t start_t, end_t;
    double total_t;
    int arr[1000];
    int arrlen = 1000;
    for(int i = 0; i < arrlen; i++){
        scanf("%d", &arr[i]);
    }
    start_t = clock();
    qsort(arr, arrlen, sizeof(int), cmp);
    end_t = clock();
    total_t = (double)(end_t - start_t) / CLOCKS_PER_SEC;
    for(int k = 0; k<arrlen; k++){
        printf("%d ", arr[k]);
    }
    printf("\n");
    printf("%lf", total_t);
    return 0;
}