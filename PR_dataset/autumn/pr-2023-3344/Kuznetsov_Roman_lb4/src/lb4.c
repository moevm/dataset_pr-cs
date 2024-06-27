#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void bsort(int* arr, int size){
    for (int i = 0; i < size - 1; i++){
        for (int j = 0; j < size - i - 1; j++){
            if (arr[j] > arr[j + 1]){
                int sort = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = sort;
            }
        }
    }
}

int compare(const void *a, const void *b){
    return (*(int *)a - *(int *)b);
}

int main(){
    int* arr = (int*)malloc(sizeof(int) * 1000);
    int* arr_copy = (int*)malloc(sizeof(int) * 1000);
    
    for (int i = 0; i < 1000; i++) scanf("%d", &arr[i]);
    
    for (int i = 0; i < 1000; i++) arr_copy[i] = arr[i];

    clock_t s_bubble = clock();
    bsort(arr, 1000);
    clock_t e_bubble = clock();

    clock_t s_qsort = clock();
    qsort(arr_copy, 1000, sizeof(int), compare);
    clock_t e_qsort = clock();

    for (int i = 0; i < 1000; i++) printf("%d ", arr[i]);
    
    printf("\n");
    printf("%lf\n", (double)(e_bubble - s_bubble) / CLOCKS_PER_SEC);
    printf("%lf\n", (double)(e_qsort - s_qsort) / CLOCKS_PER_SEC);
    
    free(arr);
    free(arr_copy);
    return 0;
}

