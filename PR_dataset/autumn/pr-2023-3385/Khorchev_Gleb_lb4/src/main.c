#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#define SIZE 1000

void bubble_sort(int* arr, int size_of_arr){
    for(size_t i=0; i<size_of_arr-1;i++){
        for(size_t j=0; j<size_of_arr-1-i; j++){
            if( arr[j] > arr[j+1]){
                int tmp = arr[j];
                arr[j] = arr[j+1];
                arr[j+1] = tmp;
            }
       }
   }

}

int cmp(const void* a, const void* b){
    const int* s = (const int*)a;
    const int* f = (const int*)b;
    if (*s > *f) return 1;
    if (*f < *s) return -1;
    return 0;
}

int main(){

    int arr[SIZE], arr_copy[SIZE], num;
    double time_bubble, time_qsort;
    clock_t  begin_bubble, end_bubble, begin_qsort, end_qsort;
    for(size_t i = 0; i<SIZE; i++)
    {
        scanf("%d", &num);
        arr[i] = num;
    }

    memcpy(arr_copy, arr, SIZE*sizeof(int));

    time_bubble = clock();
    bubble_sort(arr, SIZE);
    end_bubble = clock();
    time_bubble = (double)(end_bubble-begin_bubble) / CLOCKS_PER_SEC;

    time_qsort = clock();
    qsort(arr_copy, SIZE, sizeof(int), cmp);
    end_qsort = clock();
    time_qsort = (double)(end_qsort-begin_qsort) / CLOCKS_PER_SEC;

    for(size_t i=0; i<SIZE; i++) printf("%d ", arr[i]);
    printf("\n");
    printf("%f\n", time_bubble);
    printf("%f\n", time_qsort);
    return 0;

}
