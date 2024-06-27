#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define SIZE 1000

int cmp(const void *a, const void *b){
    const int *first = (const int *)a;
    const int *second = (const int *)b;
    return (*first - *second);
}

void sortingQsort(long double *time, int *arr){
    clock_t start = clock(), end;
    qsort(arr, SIZE, sizeof(int), cmp);
    end = clock();
    *time = (long double)(end - start)/CLOCKS_PER_SEC;
}

void sortingBubble(long double *time, int *arr){
    clock_t start = clock(), end;
    for(int i = 0; i < SIZE - 1; i++){
        int flag = 0;
        for(int j = 0; j < SIZE - i - 1; j++){
            if (arr[j] > arr[j + 1]){
                int tmp = arr[j + 1];
                arr[j + 1] = arr[j];
                arr[j] = tmp;
                flag = 1;
            } 
        }
        if(flag == 0)
            break;
    }
    end = clock();
    *time = (long double)(end - start)/CLOCKS_PER_SEC;
}

int main(){
    long double bubble_time = 0, qsort_time = 0;
    int arr_1[SIZE], arr_2[SIZE];
    
    for(int i = 0; i < SIZE; i++){
        scanf("%d", &arr_1[i]);
        arr_2[i] = arr_1[i];
    }
    
    sortingBubble(&bubble_time, arr_1);
    sortingQsort(&qsort_time, arr_2);
    for(int i = 0; i < SIZE; i++)
        printf("%d ", arr_2[i]);
    printf("\n");
    printf("%Lf\n%Lf", bubble_time, qsort_time);
    
    return 0;
}
