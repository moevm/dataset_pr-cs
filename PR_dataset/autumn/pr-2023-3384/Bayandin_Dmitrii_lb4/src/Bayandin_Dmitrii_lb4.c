#include <stdio.h>
#include <stdlib.h>
#include <time.h>


int cmp(const void *a, const void *b){
    const int *f = (const int *)a;
    const int *g = (const int *)b;
    if(*f > *g){
        return 1;
    }
    if(*f < *g){
        return -1;
    }
    return 0;
}

int bubble_sorting(int arr[]){
    for(int i = 0; i < 999; i++){
        for(int j = 0; j < 999 - i; j ++){
            if(arr[j] > arr[j+1]){
                int swap = arr[j];
                arr[j] = arr[j+1];
                arr[j+1] = swap;
            }
        }
    }
    return 1;
}


int main(){
    int arr_qsort[1000];
    int arr_bsort[1000];
    for(int i = 0; i < 1000; i++){
        scanf("%d", &arr_qsort[i]);
        arr_bsort[i] = arr_qsort[i];
    }
    double start_qsort = 0.0;
    double start_bsort = 0.0;
    time_t begin_qsort = clock();
    qsort(arr_qsort, 1000, sizeof(int), cmp);
    time_t end_qsort = clock();
    start_qsort += (double)(end_qsort - begin_qsort) / CLOCKS_PER_SEC;
    time_t begin = clock();
    bubble_sorting(arr_bsort);
    time_t end = clock();
    start_bsort += (double)(end - begin) / CLOCKS_PER_SEC;
    for(int i = 0; i < 1000; i++){
        printf("%d ", arr_qsort[i]);
    }
    printf("\n%f\n", start_bsort);
    printf("%f", start_qsort);
    return 0;
}
