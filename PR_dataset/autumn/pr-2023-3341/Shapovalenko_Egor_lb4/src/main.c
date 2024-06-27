#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define SIZE 1000

time_t bubble_sort(int *arr){
    time_t start_time = time(NULL);
    
    for(int i = 0; i < SIZE - 1; i++){
        for(int j = 0; j < SIZE - 1; j++){
            if(arr[j] > arr[j + 1]){
                int tmp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = tmp;
            }
        }
    }
    
    return time(NULL) - start_time;
}

int compare(const void * value_a, const void * value_b){
  return ( *(int*)value_a - *(int*)value_b );
}

void input(int *arr_bubble_sort, int *arr_qsort){
    for(int i = 0; i < SIZE; i++){
        scanf("%d", &arr_bubble_sort[i]);
		arr_qsort[i] = arr_bubble_sort[i];
    }
}

void output(int *arr, int bubble_sort_time, int qsort_time){
    for(int i = 0; i < SIZE; i++){
        printf("%d ", arr[i]);
    }
    printf("\n%d\n%d", bubble_sort_time, qsort_time);
}

int main(){
    int arr_bubble_sort[SIZE], arr_qsort[SIZE];
    input(arr_bubble_sort, arr_qsort);
    
    time_t bubble_sort_time = bubble_sort(arr_bubble_sort);
    
    time_t qsort_time = time(NULL);
    qsort(arr_qsort, SIZE, sizeof(int), compare);
    qsort_time = time(NULL) - qsort_time;
    
    output(arr_qsort, bubble_sort_time, qsort_time);
    
    return 0;
}
