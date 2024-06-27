#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#define N 1000

int cmp(const void *a, const void *b){
    int* f = (int*)a;
    int* s = (int*)b;
    if (*f > *s){
        return 1;
    }
    if (*f < *s){
        return -1;
    }
    return 0;
}

void swap(int* x, int* y){
    int temp = *x;
    *x = *y;
    *y = temp;
}

void bublesort(int arr[], int n){
    int i, j;
    bool swapped;
    for(i = 0; i < n - 1; i++){
        swapped = false;
        for(j = 0; j < n - i- 1; j++){
            if(arr[j] > arr[j+1]){
                swap(&arr[j], &arr[j+1]);
                swapped = true;
            }
        }
        if(swapped == false){
            break;
        }
    }
}


int main(){
    int arr[N];
    for(int i = 0; i < N; i++){
        scanf("%d", &arr[i]);
    }
    
    time_t start1, end1;
    start1 = clock();
    bublesort(arr, N);
    end1 = clock();
    double time1 = (double)(end1 - start1) / CLOCKS_PER_SEC;
    
    time_t start2, end2;
    start2 = clock();
    qsort(arr, N, sizeof(int), cmp);
    end2 = clock();
    double time2 = (double)(end2 - start2) / CLOCKS_PER_SEC;
    
    for(int i = 0; i < N; i++){
        printf("%d ", arr[i]);
    }
    printf("\n");
    printf("%f\n", time1);
    printf("%f\n", time2);
    
    return 0;
}
