#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#define N 1000

int sort_numbers(const void *a, const void *b){
    const int x = *(const int *)a;
    const int y = *(const int *)b;
    return abs(y) - abs(x);
}

int main(){
    int arr[N];
    for (int i = 0; i < N; i++){
        scanf("%d", &arr[i]);
    }
    clock_t time_start = clock(); //определяем время начала быстрой сортировки
    qsort(arr, N, sizeof(int), sort_numbers);
    clock_t time_finish = clock() - time_start; //определяем продолжительность
    
    for (int i = 0; i < N; i++){
        printf("%d ", arr[i]);
    }
    printf("\n%ld", time_finish);
    return 0;
}
