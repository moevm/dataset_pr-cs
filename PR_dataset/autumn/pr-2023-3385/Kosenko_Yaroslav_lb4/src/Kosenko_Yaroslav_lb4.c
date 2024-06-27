#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define N 1000

int compare(const void *a, const void *b){
    return (abs(*(int*)b) - abs(*(int*)a));
}

int main(){
    int arr[N];
    for (int i = 0; i < N; i++){
        scanf("%d", &arr[i]);
    }
    
    time_t start, end;
    start = clock();
    qsort(arr, N, sizeof(int), compare);
    end = clock();
    
    for (int i = 0; i < N; i++){
        printf("%d ", arr[i]);
    }
    printf("\n%lf", (double)(end - start)/CLOCKS_PER_SEC);
}