#include <stdio.h>
#include <time.h>
#include <stdlib.h>

int comp(const int *a, const int *b);

int main(){
    int arr[1000];
    for(size_t i = 0; i < 1000; i++){
        scanf("%d", &arr[i]);
    }
    clock_t str_time = clock();
    qsort(arr, 1000, sizeof(int), comp);
    clock_t end_time = clock();
    for(size_t i = 0; i < 1000; i++){
        printf("%d ", arr[i]);
    }
    printf("\n%d", end_time - str_time);
    return 0;
}

int comp(const int *a, const int *b){
    return *b - *a;    
}
